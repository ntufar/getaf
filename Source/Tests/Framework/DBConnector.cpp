#include "gtest/gtest.h"
#include "Framework/DBConnector.h" // This file doesn't exist yet

TEST(DBConnectorTest, CanConnectToDatabase) {
    DBConnector connector("localhost", "user", "password", "test_db");
    ASSERT_TRUE(connector.isConnected());
}

TEST(DBConnectorTest, CanExecuteQuery) {
    DBConnector connector("localhost", "user", "password", "test_db");
    ASSERT_TRUE(connector.isConnected());
    QueryResult result = connector.executeQuery("SELECT 1;");
    ASSERT_TRUE(result.success);
}
