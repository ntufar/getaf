#include "ConfigReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Placeholder for XML to JSON conversion. In a real scenario, a robust XML parser would be used.
// This simple function attempts to convert a very basic XML structure to JSON.
// It's highly limited and for demonstration purposes only.
nlohmann::json convertSimpleXmlToJson(const std::string& xmlContent) {
    nlohmann::json j;
    std::string currentTag;
    std::string currentValue;
    std::istringstream iss(xmlContent);
    std::string line;

    while (std::getline(iss, line)) {
        size_t startTag = line.find("< ");
        size_t endTag = line.find(">");
        if (startTag != std::string::npos && endTag != std::string::npos) {
            currentTag = line.substr(startTag + 1, endTag - startTag - 1);
            size_t valueStart = endTag + 1;
            size_t valueEnd = line.find("</" + currentTag + ">");
            if (valueEnd != std::string::npos) {
                currentValue = line.substr(valueStart, valueEnd - valueStart);
                j[currentTag] = currentValue;
            }
        }
    }
    return j;
}

ConfigReader::ConfigReader()
{
}

bool ConfigReader::LoadXml(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file: " << filePath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string xmlContent = buffer.str();

    // Attempt to convert simple XML to JSON
    configData = convertSimpleXmlToJson(xmlContent);

    std::cout << "ConfigReader: Loaded XML from " << filePath << std::endl;
    return true;
}

std::string ConfigReader::GetValue(const std::string& key, const std::string& defaultValue) const
{
    // This is a very basic implementation. For nested keys, a more sophisticated approach is needed.
    if (configData.contains(key)) {
        return configData[key].get<std::string>();
    }
    return defaultValue;
}

bool ConfigReader::HasKey(const std::string& key) const
{
    return configData.contains(key);
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