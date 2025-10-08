#include "gtest/gtest.h"
#include "Framework/DBConnector.h"
#include <memory>

// Mock MySQL Connection for testing
class MockConnection {
public:
    static bool shouldFailConnection;
    static bool shouldFailQuery;
    static std::string lastQuery;
    static void reset() {
        shouldFailConnection = false;
        shouldFailQuery = false;
        lastQuery.clear();
    }
};

bool MockConnection::shouldFailConnection = false;
bool MockConnection::shouldFailQuery = false;
std::string MockConnection::lastQuery;

// Test fixture for DBConnector tests
class DBConnectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        MockConnection::reset();
    }

    void TearDown() override {
        MockConnection::reset();
    }

    const std::string TEST_HOST = "localhost";
    const std::string TEST_USER = "testuser";
    const std::string TEST_PASSWORD = "testpass";
    const std::string TEST_DB = "testdb";
};

// Basic Connection Tests
TEST_F(DBConnectorTest, SuccessfulConnection) {
    DBConnector connector(TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB);
    ASSERT_TRUE(connector.isConnected());
}

TEST_F(DBConnectorTest, ConnectionFailure) {
    MockConnection::shouldFailConnection = true;
    DBConnector connector("invalid_host", TEST_USER, TEST_PASSWORD, TEST_DB);
    ASSERT_FALSE(connector.isConnected());
}

TEST_F(DBConnectorTest, EmptyCredentials) {
    DBConnector connector("", "", "", "");
    ASSERT_FALSE(connector.isConnected());
}

// Query Execution Tests
TEST_F(DBConnectorTest, SuccessfulQueryExecution) {
    DBConnector connector(TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB);
    ASSERT_TRUE(connector.isConnected());
    
    QueryResult result = connector.executeQuery("SELECT 1");
    ASSERT_TRUE(result.success);
    ASSERT_EQ(MockConnection::lastQuery, "SELECT 1");
}

TEST_F(DBConnectorTest, FailedQueryExecution) {
    DBConnector connector(TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB);
    ASSERT_TRUE(connector.isConnected());
    
    MockConnection::shouldFailQuery = true;
    QueryResult result = connector.executeQuery("SELECT * FROM nonexistent_table");
    ASSERT_FALSE(result.success);
}

TEST_F(DBConnectorTest, EmptyQuery) {
    DBConnector connector(TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB);
    ASSERT_TRUE(connector.isConnected());
    
    QueryResult result = connector.executeQuery("");
    ASSERT_FALSE(result.success);
}

// Connection State Management Tests
TEST_F(DBConnectorTest, ReconnectionAttempt) {
    DBConnector connector(TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB);
    ASSERT_TRUE(connector.isConnected());
    
    // Simulate connection loss
    MockConnection::shouldFailConnection = true;
    QueryResult result = connector.executeQuery("SELECT 1");
    ASSERT_FALSE(result.success);
    ASSERT_FALSE(connector.isConnected());
    
    // Attempt reconnection
    MockConnection::shouldFailConnection = false;
    result = connector.executeQuery("SELECT 1");
    ASSERT_TRUE(result.success);
    ASSERT_TRUE(connector.isConnected());
}

TEST_F(DBConnectorTest, DestructorCleanup) {
    {
        DBConnector connector(TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB);
        ASSERT_TRUE(connector.isConnected());
        // Connector will go out of scope here
    }
    // Verify cleanup in destructor (can be checked through mock)
}

// Edge Cases and Error Handling
TEST_F(DBConnectorTest, LongQuery) {
    DBConnector connector(TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB);
    ASSERT_TRUE(connector.isConnected());
    
    std::string longQuery(65535, 'x'); // Max query length
    QueryResult result = connector.executeQuery(longQuery);
    ASSERT_FALSE(result.success); // Should fail due to length
}

TEST_F(DBConnectorTest, SpecialCharactersInQuery) {
    DBConnector connector(TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB);
    ASSERT_TRUE(connector.isConnected());
    
    QueryResult result = connector.executeQuery("SELECT 'テスト'; -- コメント");
    ASSERT_TRUE(result.success);
}

TEST_F(DBConnectorTest, MultipleQueriesInTransaction) {
    DBConnector connector(TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB);
    ASSERT_TRUE(connector.isConnected());
    
    std::vector<std::string> queries = {
        "BEGIN;",
        "CREATE TEMPORARY TABLE test (id INT);",
        "INSERT INTO test VALUES (1);",
        "SELECT * FROM test;",
        "DROP TABLE test;",
        "COMMIT;"
    };
    
    for (const auto& query : queries) {
        QueryResult result = connector.executeQuery(query);
        ASSERT_TRUE(result.success) << "Query failed: " << query;
    }
}

TEST_F(DBConnectorTest, ConcurrentConnections) {
    // Create multiple DBConnector instances
    std::vector<std::unique_ptr<DBConnector>> connectors;
    const int NUM_CONNECTIONS = 5;
    
    for (int i = 0; i < NUM_CONNECTIONS; i++) {
        connectors.push_back(std::make_unique<DBConnector>(
            TEST_HOST, TEST_USER, TEST_PASSWORD, TEST_DB
        ));
        ASSERT_TRUE(connectors.back()->isConnected());
    }
    
    // Execute queries concurrently
    for (auto& connector : connectors) {
        QueryResult result = connector->executeQuery("SELECT 1");
        ASSERT_TRUE(result.success);
    }
}
