CREATE TABLE TestExecution (
    execution_id INT AUTO_INCREMENT PRIMARY KEY,
    timestamp DATETIME NOT NULL,
    branch_name VARCHAR(255),
    commit_hash VARCHAR(40),
    status ENUM('running', 'completed', 'failed') NOT NULL
);

CREATE TABLE TestResult (
    result_id INT AUTO_INCREMENT PRIMARY KEY,
    execution_id INT,
    test_name VARCHAR(255) NOT NULL,
    duration_ms INT,
    outcome ENUM('pass', 'fail', 'skipped', 'error') NOT NULL,
    error_message TEXT,
    stack_trace TEXT,
    FOREIGN KEY (execution_id) REFERENCES TestExecution(execution_id)
);

CREATE TABLE PerformanceMetric (
    metric_id INT AUTO_INCREMENT PRIMARY KEY,
    execution_id INT,
    test_name VARCHAR(255),
    metric_type ENUM('fps', 'memory_mb', 'cpu_percent') NOT NULL,
    value FLOAT NOT NULL,
    timestamp DATETIME NOT NULL,
    FOREIGN KEY (execution_id) REFERENCES TestExecution(execution_id)
);

CREATE TABLE PerformanceBaseline (
    baseline_id INT AUTO_INCREMENT PRIMARY KEY,
    test_name VARCHAR(255) NOT NULL,
    metric_type ENUM('fps', 'memory_mb', 'cpu_percent') NOT NULL,
    expected_value FLOAT NOT NULL,
    tolerance_percent FLOAT NOT NULL
);