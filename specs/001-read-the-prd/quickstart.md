# Quickstart: Validating a Game Build

This guide walks through the primary user story of using GETAF to validate a new game build.

## Prerequisites

1.  A new game build is available and deployed to a test environment.
2.  The GETAF framework is configured to target the test environment.
3.  The test database is running and accessible.

## Steps

### 1. Trigger the CI/CD Pipeline
A QA Engineer pushes a commit to a feature branch or merges a PR to `main`. This action automatically triggers the "Run Tests" workflow in GitHub Actions.

```yaml
# .github/workflows/main.yml (conceptual)
on: [push]

jobs:
  test:
    runs-on: windows-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v3

      - name: Run GETAF Test Suite
        run: |
          # This command would execute the C# test runner
          dotnet test
```

### 2. Monitor Test Execution
The C# test runner invokes the C++ core framework, which executes the tests against the game build.
- Unit, integration, and system tests are run.
- Performance metrics (FPS, memory) are collected in real-time.

### 3. Review the Results
Upon completion, the test results and performance data are persisted to the MySQL database.
- A test report is generated and uploaded as a build artifact.
- The QA Engineer can download and review the report.

### 4. Identify Regressions
The report will clearly flag:
- **Functional Regressions**: Any test case that failed.
- **Performance Regressions**: Any performance metric that breached its baseline threshold (e.g., FPS dropped by more than 10%).

### Example Acceptance Scenario

- **Given**: A performance test for the main level has a baseline of 60 FPS.
- **When**: The test is executed against a new build, and the average FPS is 50.
- **Then**: The final report flags a performance regression for the main level test, indicating a 16.7% drop in FPS.
