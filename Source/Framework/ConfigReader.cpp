#include "ConfigReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "tinyxml2.h" // Include TinyXML2 header

// Helper function to recursively parse XML nodes into nlohmann::json
void parseXmlNodeToJson(const tinyxml2::XMLElement* element, nlohmann::json& jsonNode) {
    if (!element) {
        return;
    }

    // Add attributes
    for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()) {
        jsonNode["@" + std::string(attr->Name())] = attr->Value();
    }

    // Add child elements
    for (const tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement()) {
        nlohmann::json childJson;
        parseXmlNodeToJson(child, childJson);

        std::string tagName = child->Name();
        if (jsonNode.contains(tagName)) {
            // If tag already exists, convert to array
            if (!jsonNode[tagName].is_array()) {
                nlohmann::json temp = jsonNode[tagName];
                jsonNode[tagName] = nlohmann::json::array();
                jsonNode[tagName].push_back(temp);
            }
            jsonNode[tagName].push_back(childJson);
        } else {
            jsonNode[tagName] = childJson;
        }
    }

    // Add text content if no child elements
    if (!element->FirstChildElement() && element->GetText()) {
        jsonNode["#text"] = element->GetText();
    }
}

ConfigReader::ConfigReader()
{
}

bool ConfigReader::LoadXml(const std::string& filePath)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error: Could not load XML file: " << filePath << " - " << doc.ErrorStr() << std::endl;
        return false;
    }

    configData.clear();
    parseXmlNodeToJson(doc.RootElement(), configData);

    std::cout << "ConfigReader: Loaded XML from " << filePath << std::endl;
    return true;
}

std::string ConfigReader::GetValue(const std::string& key, const std::string& defaultValue) const
{
    nlohmann::json current = configData;
    std::istringstream iss(key);
    std::string segment;

    while (std::getline(iss, segment, '.')) {
        if (current.contains(segment)) {
            current = current[segment];
        } else {
            return defaultValue;
        }
    }

    if (current.is_string()) {
        return current.get<std::string>();
    } else if (current.is_number()) {
        return std::to_string(current.get<double>());
    } else if (current.is_boolean()) {
        return current.get<bool>() ? "true" : "false";
    }
    return defaultValue;
}

bool ConfigReader::HasKey(const std::string& key) const
{
    nlohmann::json current = configData;
    std::istringstream iss(key);
    std::string segment;

    while (std::getline(iss, segment, '.')) {
        if (current.contains(segment)) {
            current = current[segment];
        } else {
            return false;
        }
    }
    return true;
}

// C++/C# Bridge functions (from ConfigReader.h)
extern "C" FRAMEWORK_API int GetAnswer() {
    return 42;
}

extern "C" FRAMEWORK_API bool TriggerGauntletTest(const char* testName) {
    std::cout << "C++ Framework: Simulating triggering Gauntlet test: " << testName << std::endl;
    // In a real scenario, this would involve calling UE5 Gauntlet APIs or a command-line tool.
    return true;
}