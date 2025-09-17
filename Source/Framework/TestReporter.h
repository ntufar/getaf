#pragma once

#include <string>
#include "DBConnector.h"

class TestReporter
{
public:
    TestReporter(DBConnector& connector);
    void ReportTestResult(const std::string& testName, int durationMs, const std::string& outcome, const std::string& errorMessage = "", const std::string& stackTrace = "");
    void ReportPerformanceMetric(const std::string& testName, const std::string& metricType, float value);

private:
    DBConnector& dbConnector;
};