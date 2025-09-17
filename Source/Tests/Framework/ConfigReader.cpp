#include "gtest/gtest.h"
#include "Framework/ConfigReader.h" // This file doesn't exist yet
#include <fstream>

TEST(ConfigReaderTest, CanReadNonExistentFile) {
    ConfigReader reader("non_existent_file.json");
    ASSERT_FALSE(reader.isValid());
}

TEST(ConfigReaderTest, CanReadValidJson) {
    // Create a dummy json file for testing
    std::ofstream outfile("test_config.json");
    outfile << "{ \"key\": \"value\" }";
    outfile.close();

    ConfigReader reader("test_config.json");
    ASSERT_TRUE(reader.isValid());
    EXPECT_EQ(reader.getString("key"), "value");
}
