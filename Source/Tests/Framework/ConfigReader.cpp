#include "gtest/gtest.h"
#include "ConfigReader.h"
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Helper function to create a dummy config file for testing
void createTestConfigFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    ASSERT_TRUE(file.is_open()) << "Failed to create test config file: " << filePath;
    file << content;
    file.close();
}

class ConfigReaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test config files
        createTestConfigFile("test_config.xml", 
            R"(<?xml version="1.0" encoding="UTF-8"?>
            <config>
                <setting name="LogLevel" value="INFO"/>
                <database>
                    <host>localhost</host>
                    <port>3306</port>
                    <user>testuser</user>
                    <password>testpass</password>
                </database>
                <features>
                    <feature name="FeatureA" enabled="true"/>
                    <feature name="FeatureB" enabled="false"/>
                </features>
            </config>)");
        
        createTestConfigFile("malformed_config.xml",
            R"(<?xml version="1.0" encoding="UTF-8"?>
            <config>
                <setting>Incomplete tag
                <database>
                    Missing closing tags
            </config>)");
        
        createTestConfigFile("empty_config.xml", "");

        createTestConfigFile("advanced_config.xml",
            R"(<?xml version="1.0" encoding="UTF-8"?>
            <root>
                <item>
                    <name>Item A</name>
                    <value>100</value>
                </item>
                <item>
                    <name>Item B</name>
                    <value>200</value>
                </item>
                <description>This is a <bold>description</bold> with mixed content.</description>
                <simpleText>Just some text.</simpleText>
                <numericValue>123</numericValue>
                <booleanValue>true</booleanValue>
            </root>)");
    }

    void TearDown() override {
        // Clean up test files
        std::remove("test_config.xml");
        std::remove("malformed_config.xml");
        std::remove("empty_config.xml");
        std::remove("advanced_config.xml");
    }
};

TEST_F(ConfigReaderTest, LoadValidXmlFile) {
    ConfigReader reader;
    ASSERT_TRUE(reader.LoadXml("test_config.xml"));
}

TEST_F(ConfigReaderTest, GetValueFromValidXml) {
    ConfigReader reader;
    ASSERT_TRUE(reader.LoadXml("test_config.xml"));
    // Now with TinyXML2, we expect specific values
    ASSERT_EQ(reader.GetValue("config.setting.@name"), "LogLevel");
    ASSERT_EQ(reader.GetValue("config.setting.@value"), "INFO");
    ASSERT_EQ(reader.GetValue("config.database.host"), "localhost");
    ASSERT_EQ(reader.GetValue("config.database.port"), "3306");
    ASSERT_EQ(reader.GetValue("config.features.feature.@name"), "FeatureA"); // Only gets the first feature
}

TEST_F(ConfigReaderTest, GetValueNestedKeys) {
    ConfigReader reader;
    ASSERT_TRUE(reader.LoadXml("test_config.xml"));
    ASSERT_EQ(reader.GetValue("config.database.user"), "testuser");
    ASSERT_EQ(reader.GetValue("config.database.password"), "testpass");
}

TEST_F(ConfigReaderTest, GetValueAttributes) {
    ConfigReader reader;
    ASSERT_TRUE(reader.LoadXml("test_config.xml"));
    ASSERT_EQ(reader.GetValue("config.features.feature.@enabled"), "true");
}

TEST_F(ConfigReaderTest, GetValueWithDefault) {
    ConfigReader reader;
    ASSERT_TRUE(reader.LoadXml("test_config.xml"));
    // Test default value for non-existent key
    ASSERT_EQ(reader.GetValue("nonexistent.key", "default"), "default");
    // Test default value when key exists
    ASSERT_NE(reader.GetValue("config.setting.@value", "default"), "default");
}

TEST_F(ConfigReaderTest, GetAnswerBridgeFunction) {
    ASSERT_EQ(GetAnswer(), 42);
}

TEST_F(ConfigReaderTest, TriggerGauntletTestBridgeFunction) {
    ASSERT_TRUE(TriggerGauntletTest("TestMap_01"));
    ASSERT_TRUE(TriggerGauntletTest("")); // Edge case: empty string
}

TEST_F(ConfigReaderTest, HasKeyTests) {
    ConfigReader reader;
    ASSERT_TRUE(reader.LoadXml("test_config.xml"));
    
    ASSERT_TRUE(reader.HasKey("config.setting"));
    ASSERT_TRUE(reader.HasKey("config.database.host"));
    ASSERT_TRUE(reader.HasKey("config.features.feature.@name"));
    ASSERT_FALSE(reader.HasKey(""));  // Empty key
    ASSERT_FALSE(reader.HasKey("nonexistent.key"));
}

TEST_F(ConfigReaderTest, LoadNonExistentFile) {
    ConfigReader reader;
    ASSERT_FALSE(reader.LoadXml("non_existent.xml"));
    ASSERT_TRUE(reader.GetValue("any_key").empty());
}

TEST_F(ConfigReaderTest, LoadMalformedXmlFile) {
    ConfigReader reader;
    ASSERT_FALSE(reader.LoadXml("malformed_config.xml"));
    // With TinyXML2, malformed XML should result in an empty configData
    ASSERT_FALSE(reader.HasKey("config.setting"));
    ASSERT_TRUE(reader.GetValue("config.setting.@value").empty());
}

TEST_F(ConfigReaderTest, LoadEmptyFile) {
    ConfigReader reader;
    ASSERT_FALSE(reader.LoadXml("empty_config.xml"));
    ASSERT_FALSE(reader.HasKey("any_key"));
    ASSERT_TRUE(reader.GetValue("any_key").empty());
}

TEST_F(ConfigReaderTest, MultipleLoads) {
    ConfigReader reader;
    
    // First load
    ASSERT_TRUE(reader.LoadXml("test_config.xml"));
    std::string firstValue = reader.GetValue("config.setting.@value");
    
    // Second load of the same file
    ASSERT_TRUE(reader.LoadXml("test_config.xml"));
    ASSERT_EQ(reader.GetValue("config.setting.@value"), firstValue);
    
    // Load invalid file after valid file
    ASSERT_FALSE(reader.LoadXml("malformed_config.xml"));
    // Previous values should be cleared
    ASSERT_TRUE(reader.GetValue("config.setting.@value").empty());
}

TEST_F(ConfigReaderTest, LoadAdvancedXmlFileAndGetValues) {
    ConfigReader reader;
    ASSERT_TRUE(reader.LoadXml("advanced_config.xml"));

    // Test text content directly within a node
    ASSERT_EQ(reader.GetValue("root.simpleText.#text"), "Just some text.");

    // Test mixed content (TinyXML2 might put it under #text or ignore tags within text)
    // Depending on how parseXmlNodeToJson handles mixed content, this might need adjustment.
    // For now, we expect it to capture the text content.
    ASSERT_EQ(reader.GetValue("root.description.#text"), "This is a description with mixed content.");

    // Test multiple elements of the same name (should get the first one)
    ASSERT_EQ(reader.GetValue("root.item.name.#text"), "Item A");
    ASSERT_EQ(reader.GetValue("root.item.value.#text"), "100");

    // Test different data types
    ASSERT_EQ(reader.GetValue("root.numericValue.#text"), "123");
    ASSERT_EQ(reader.GetValue("root.booleanValue.#text"), "true");
}

TEST_F(ConfigReaderTest, HasKeyAdvancedXml) {
    ConfigReader reader;
    ASSERT_TRUE(reader.LoadXml("advanced_config.xml"));

    ASSERT_TRUE(reader.HasKey("root.simpleText.#text"));
    ASSERT_TRUE(reader.HasKey("root.description.#text"));
    ASSERT_TRUE(reader.HasKey("root.item.name.#text"));
    ASSERT_TRUE(reader.HasKey("root.numericValue.#text"));
    ASSERT_TRUE(reader.HasKey("root.booleanValue.#text"));
    ASSERT_FALSE(reader.HasKey("root.nonExistentKey"));
}