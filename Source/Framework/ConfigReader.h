#pragma once

#include <string>
#include "json.hpp" // Include nlohmann/json header
#include "tinyxml2.h" // Include TinyXML2 header

// For the C++/C# bridge placeholder
#ifdef _WIN32
    #ifdef FRAMEWORK_EXPORTS
        #define FRAMEWORK_API __declspec(dllexport)
    #else
        #define FRAMEWORK_API __declspec(dllimport)
    #endif
#else
    #define FRAMEWORK_API
#endif

extern "C" FRAMEWORK_API int GetAnswer();
extern "C" FRAMEWORK_API bool TriggerGauntletTest(const char* testName);

class ConfigReader
{
public:
    ConfigReader();
    bool LoadXml(const std::string& filePath);
    std::string GetValue(const std::string& key, const std::string& defaultValue = "") const;
    bool HasKey(const std::string& key) const;

private:
    nlohmann::json configData;
};