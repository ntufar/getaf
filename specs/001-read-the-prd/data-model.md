# Data Model

This document outlines the key data entities for the GETAF project, based on the feature specification.

## Entity Relationship Diagram (Conceptual)

```
+--------------------+      +------------------+
|   TestExecution    |----->|    TestResult    |
+--------------------+      +------------------+
        |
        |
        v
+--------------------+
| PerformanceMetric  |
+--------------------+
```

## Entities

### TestExecution
Represents a single run of the entire test suite.
- **Attributes**:
    - `execution_id` (Primary Key)
    - `timestamp` (DateTime)
    - `branch_name` (String)
    - `commit_hash` (String)
    - `status` (Enum: 'running', 'completed', 'failed')

### TestResult
Represents the outcome of an individual test case.
- **Attributes**:
    - `result_id` (Primary Key)
    - `execution_id` (Foreign Key to TestExecution)
    - `test_name` (String)
    - `duration_ms` (Integer)
    - `outcome` (Enum: 'pass', 'fail', 'skipped', 'error')
    - `error_message` (Text, nullable)
    - `stack_trace` (Text, nullable)

### PerformanceMetric
Represents a single performance measurement captured during a test execution.
- **Attributes**:
    - `metric_id` (Primary Key)
    - `execution_id` (Foreign Key to TestExecution)
    - `test_name` (String, nullable)
    - `metric_type` (Enum: 'fps', 'memory_mb', 'cpu_percent')
    - `value` (Float)
    - `timestamp` (DateTime)

### PerformanceBaseline
Represents the expected performance metrics for a given test scenario.
- **Attributes**:
    - `baseline_id` (Primary Key)
    - `test_name` (String)
    - `metric_type` (Enum: 'fps', 'memory_mb', 'cpu_percent')
    - `expected_value` (Float)
    - `tolerance_percent` (Float)

### TestConfiguration
Represents the parameters and data used to drive data-driven tests. This entity is conceptual and is stored as version-controlled XML/JSON files, not in the database.
- **Source**: `Config/` directory in the repository.
