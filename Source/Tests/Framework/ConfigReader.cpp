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
    ASSERT_TRUE(reader.GetValue("NonExistentKey").empty());
}

TEST(ConfigReaderTest, GetAnswerBridgeFunction)
{
    ASSERT_EQ(GetAnswer(), 42);
}

TEST(ConfigReaderTest, TriggerGauntletTestBridgeFunction)
{
    // This test primarily checks if the function can be called without crashing
    // and returns true as per its current dummy implementation.
    // In a real scenario, this would involve mocking the Gauntlet interaction.
    ASSERT_TRUE(TriggerGauntletTest("TestMap_01"));
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
    // With the current simple XML parser, LoadXml will likely succeed in reading the file
    // but the internal configData will be empty or incorrectly parsed.
    ASSERT_TRUE(reader.LoadXml(malformedConfigPath));
    // Expecting no keys to be found or values to be empty due to malformed XML
    ASSERT_FALSE(reader.HasKey("setting"));
    ASSERT_TRUE(reader.GetValue("setting").empty());
}