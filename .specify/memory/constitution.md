# GETAF Project Constitution

This document outlines the fundamental principles, architecture, and requirements of the Game Engine Test Automation Framework (GETAF). All development must align with this constitution.

## 1. Project Goal

To develop a comprehensive, production-ready test automation framework for 3D games built with Unreal Engine 5. The framework will demonstrate enterprise-level testing practices, CI/CD integration, and technical leadership in game development quality assurance.

## 2. Core Technologies

- **Primary Languages:** C++ (17/20), C# (.NET 6)
- **Game Engine:** Unreal Engine 5.x
- **Testing Frameworks:** GoogleTest, NUnit
- **Build System:** CMake
- **Database:** MySQL Community Server 8.0
- **CI/CD:** GitHub Actions
- **Version Control:** Git/GitHub
- **Scripting:** Python, PowerShell

## 3. System Architecture

The framework follows a multi-layer architecture:
1.  **CI/CD Pipeline (GitHub Actions):** Orchestrates builds and test execution.
2.  **Test Execution Layer (C# / Python / UE5 Gauntlet):** Manages test execution and scripting.
3.  **Core Test Framework (C++):** Provides the foundational testing capabilities (e.g., assertions, configuration, reporting) using GoogleTest.
4.  **Game Under Test (Unreal Engine 5):** The target game project being tested.

## 4. Core Functional Requirements

- **FR-001:** Implement a multi-layer testing pyramid (Unit, Integration, System).
- **FR-002:** Ensure seamless integration between the C++ core and C# scripting layer.
- **FR-003:** Enable data-driven test execution from XML/JSON configuration files.
- **FR-004:** Integrate natively with UE5's automation systems (Gauntlet).
- **FR-005:** Achieve comprehensive test coverage of core game features (Character, AI, UI, etc.).
- **FR-006:** Implement real-time collection of performance metrics (FPS, memory).
- **FR-007:** Automatically detect performance regressions against a defined baseline.
- **FR-008:** Provide a framework for testing HTTP REST APIs.
- **FR-009:** Test database connectivity and data integrity.

## 5. Core Non-Functional Requirements

- **Build & Test Time:** The full CI pipeline execution must take less than 10 minutes.
- **Code Coverage:** All modules must maintain a code coverage of greater than 80%.
- **Stability:** The framework must have 99.5% uptime and handle failures gracefully.
- **Scalability:** The system must support a growing suite of 1000+ test cases and allow for parallel execution.

## 6. Project Structure

The project must adhere to the following directory structure:

```
GameTestFramework/
├── Source/
│   ├── Framework/          # Core C++ test framework
│   ├── GameLogic/         # Simple game implementation
│   └── Tests/             # Test implementations
├── Scripts/               # Python/PowerShell automation
├── Config/               # XML configuration files
├── Database/            # MySQL schemas and scripts
├── CI/                  # GitHub Actions workflows
└── Documentation/       # Project docs and guides
```
