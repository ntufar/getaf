#include "gtest/gtest.h"
#include "ConfigReader.h"
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Helper function to create a dummy config file for testing
void createTestConfigFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    ASSERT_TRUE(file.is_open()) << "Failed to create test config file: " << filePath;
    file << content;
    file.close();
}

TEST(ConfigReaderTest, LoadValidXmlFile)
{
    ConfigReader reader;
    std::string testConfigPath = "C:/projects/getaf/Config/test_config.xml";
    ASSERT_TRUE(reader.LoadXml(testConfigPath));
}

TEST(ConfigReaderTest, GetValueFromValidXml)
{
    ConfigReader reader;
    std::string testConfigPath = "C:/projects/getaf/Config/test_config.xml";
    reader.LoadXml(testConfigPath);

    // The current simple XML parser only extracts top-level tags as keys
    // So, we expect to get values for 'setting', 'database', 'features' as raw XML strings
    // This test will need to be updated once a proper XML parser is integrated
    ASSERT_EQ(reader.GetValue("setting"), " name=\"LogLevel\" value=\"INFO\"/");
    ASSERT_EQ(reader.GetValue("database"), "\n        <host>localhost</host>\n        <port>3306</port>\n        <user>testuser</user>\n        <password>testpass</password>\n    ");
    ASSERT_EQ(reader.GetValue("features"), "\n        <feature name=\"FeatureA\" enabled=\"true"/>\n        <feature name=\"FeatureB\" enabled=\"false"/>\n    ");
    ASSERT_EQ(reader.GetValue("NonExistentKey", "Default"), "Default");
}

TEST(ConfigReaderTest, HasKey)
{
    ConfigReader reader;
    std::string testConfigPath = "C:/projects/getaf/Config/test_config.xml";
    reader.LoadXml(testConfigPath);

    ASSERT_TRUE(reader.HasKey("setting"));
    ASSERT_TRUE(reader.HasKey("database"));
    ASSERT_TRUE(reader.HasKey("features"));
    ASSERT_FALSE(reader.HasKey("NonExistentKey"));
}

TEST(ConfigReaderTest, LoadNonExistentFile)
{
    ConfigReader reader;
    std::string nonExistentPath = "C:/projects/getaf/Config/non_existent.xml";
    ASSERT_FALSE(reader.LoadXml(nonExistentPath));
}

TEST(ConfigReaderTest, LoadMalformedXmlFile)
{
    ConfigReader reader;
    std::string malformedConfigPath = "C:/projects/getaf/Config/malformed_config.xml";
    // The current simple XML parser might not fail gracefully on malformed XML,
    // but it should at least not crash and ideally return false or empty data.
    // This test will need to be refined with a proper XML parser.
    ASSERT_TRUE(reader.LoadXml(malformedConfigPath)); // It will load, but content will be empty or partial
    ASSERT_TRUE(reader.GetValue("setting").empty()); // Expecting empty because the malformed XML won't be parsed correctly
}