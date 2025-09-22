#include "gtest/gtest.h"
#include "Framework/TestReporter.h"
#include "Framework/DBConnector.h" // Include for DBConnector

// Mock DBConnector for testing TestReporter in isolation
class MockDBConnector : public DBConnector {
public:
    MockDBConnector() : DBConnector("mock_host", "mock_user", "mock_pass", "mock_db") {}

    // Override executeQuery to simulate database interaction
    QueryResult executeQuery(const std::string& query) override {
        // In a real mock, you'd inspect the query string and return appropriate results
        // For now, we'll just say it was successful
        lastQuery = query;
        return {true};
    }

    std::string lastQuery;
};

TEST(TestReporterTest, ReportTestResult) {
    MockDBConnector mockDb;
    TestReporter reporter(mockDb);

    std::string testName = "MyTest";
    int durationMs = 100;
    std::string outcome = "PASS";
    std::string errorMessage = "";
    std::string stackTrace = "";

    reporter.ReportTestResult(testName, durationMs, outcome, errorMessage, stackTrace);

    // Verify that the reporter attempted to execute a query
    ASSERT_FALSE(mockDb.lastQuery.empty());
    // Further assertions could check the content of mockDb.lastQuery
    // to ensure the SQL query was formed correctly.
}

TEST(TestReporterTest, ReportPerformanceMetric) {
    MockDBConnector mockDb;
    TestReporter reporter(mockDb);

    std::string testName = "MyPerformanceTest";
    std::string metricType = "FPS";
    float value = 60.5f;

    reporter.ReportPerformanceMetric(testName, metricType, value);

    // Verify that the reporter attempted to execute a query
    ASSERT_FALSE(mockDb.lastQuery.empty());
    // Further assertions could check the content of mockDb.lastQuery
    // to ensure the SQL query was formed correctly.
}
