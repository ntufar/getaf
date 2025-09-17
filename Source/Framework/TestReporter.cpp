#include "TestReporter.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

TestReporter::TestReporter(DBConnector& connector)
    : dbConnector(connector)
{
}

void TestReporter::ReportTestResult(const std::string& testName, int durationMs, const std::string& outcome, const std::string& errorMessage, const std::string& stackTrace)
{
    if (!dbConnector.isConnected()) {
        std::cerr << "TestReporter: Not connected to database. Cannot report test result." << std::endl;
        return;
    }

    // Get current timestamp
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    std::string timestamp = ss.str();

    // For simplicity, we'll assume a dummy execution_id for now.
    // In a real scenario, an execution_id would be generated at the start of a test run.
    int executionId = 1; 

    std::string query = "INSERT INTO TestResult (execution_id, test_name, duration_ms, outcome, error_message, stack_trace) VALUES (";
    query += std::to_string(executionId) + ", '";
    query += testName + "', ";
    query += std::to_string(durationMs) + ", '";
    query += outcome + "', '";
    query += errorMessage + "', '";
    query += stackTrace + "')";

    QueryResult result = dbConnector.executeQuery(query);
    if (result.success) {
        std::cout << "Test result for '" << testName << "' reported successfully." << std::endl;
    } else {
        std::cerr << "Failed to report test result for '" << testName << "'" << std::endl;
    }
}

void TestReporter::ReportPerformanceMetric(const std::string& testName, const std::string& metricType, float value)
{
    if (!dbConnector.isConnected()) {
        std::cerr << "TestReporter: Not connected to database. Cannot report performance metric." << std::endl;
        return;
    }

    // Get current timestamp
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
    std::string timestamp = ss.str();

    // For simplicity, we'll assume a dummy execution_id for now.
    // In a real scenario, an execution_id would be generated at the start of a test run.
    int executionId = 1; 

    std::string query = "INSERT INTO PerformanceMetric (execution_id, test_name, metric_type, value, timestamp) VALUES (";
    query += std::to_string(executionId) + ", '";
    query += testName + "', '";
    query += metricType + "', ";
    query += std::to_string(value) + ", '";
    query += timestamp + "')";

    QueryResult result = dbConnector.executeQuery(query);
    if (result.success) {
        std::cout << "Performance metric for '" << testName << "' reported successfully." << std::endl;
    } else {
        std::cerr << "Failed to report performance metric for '" << testName << "'" << std::endl;
    }
}
