# GEMINI Project Brief: Game Engine Test Automation Framework (GETAF)

This document provides a technical summary of the GETAF project based on the provided planning and requirements documents.

## 1. Project Goal

To develop a comprehensive, production-ready test automation framework for 3D games built with Unreal Engine 5, demonstrating enterprise-level testing practices and CI/CD integration. The primary objective is to build technical competency for test automation leadership roles in game development.

## 2. Core Technologies

- **Primary Languages:** C++ (17/20), C# (.NET 6)
- **Game Engine:** Unreal Engine 5.x
- **Testing Frameworks:** GoogleTest, NUnit, Catch2
- **Build System:** CMake, MSBuild
- **Database:** MySQL Community Server 8.0
- **CI/CD:** GitHub Actions
- **Version Control:** Git/GitHub
- **IDE:** Visual Studio Community 2022
- **Scripting:** Python, PowerShell

## 3. System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                     CI/CD Pipeline                         │
│                   (GitHub Actions)                         │
└─────────────────────────┬───────────────────────────────────┘
                          │
┌─────────────────────────▼───────────────────────────────────┐
│                 Test Execution Layer                       │
├─────────────────────────────────────────────────────────────┤
│  C# Test Runner    │    Python Scripts    │  UE5 Gauntlet  │
└─────────────────────────┬───────────────────────────────────┘
                          │
┌─────────────────────────▼───────────────────────────────────┐
│                  Core Test Framework                       │
├─────────────────────────────────────────────────────────────┤
│         C++ Framework Core (GoogleTest/Catch2)             │
│    Config Reader │ HTTP Client │ DB Connector │ Reporter    │
└─────────────────────────┬───────────────────────────────────┘
                          │
┌─────────────────────────▼───────────────────────────────────┐
│                 Game Under Test                            │
├─────────────────────────────────────────────────────────────┤
│                    UE5 Game Project                        │
│     Character │  Collectibles │  AI  │  UI  │  Physics     │
└─────────────────────────────────────────────────────────────┘
```

### Component Specifications:
- **Core Framework (C++):** Uses GoogleTest. Includes custom base classes, an XML/JSON config reader, and a reporting engine.
- **Integration Layer (C#):** Uses NUnit for test execution and P/Invoke for bridging to the C++ core.
- **Game Integration (UE5/C++):** Leverages the UE5 Automation plugin for native testing, including performance profiling and screenshot comparisons.
- **Data Layer (MySQL):** Stores test results, configuration, and historical performance data.

## 4. Key Requirements Summary

### Functional Requirements:
- **FR-001:** Implement a multi-layer testing pyramid (Unit, Integration, System).
- **FR-002:** Ensure seamless integration between the C++ core and C# scripting layer.
- **FR-003:** Enable data-driven test execution from XML/JSON files.
- **FR-004:** Integrate natively with UE5's automation systems (Gauntlet).
- **FR-005:** Achieve comprehensive test coverage of game features (character, AI, UI, etc.).
- **FR-006:** Implement real-time collection of performance metrics (FPS, memory).
- **FR-007:** Automatically detect performance regressions against a baseline.
- **FR-008:** Provide a framework for testing HTTP REST APIs.
- **FR-009:** Test database connectivity and data integrity.

### Non-Functional Requirements (Key Targets):
- **Build & Test Time:** Full CI pipeline < 10 minutes.
- **Code Coverage:** >80% for all modules.
- **Stability:** 99.5% framework uptime; graceful failure handling.
- **Scalability:** Support for 1000+ test cases and parallel execution.

## 5. Project Structure

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

## 6. Development Phases

- **Phase 1 (Weeks 1-3): Foundation**: Setup dev environment, build core C++ framework, and establish a basic CI/CD pipeline.
- **Phase 2 (Weeks 4-6): Game Integration**: Create a simple UE5 game and integrate it with the automation framework. Implement performance monitoring and API testing.
- **Phase 3 (Weeks 7-9): Advanced Features**: Implement data-driven testing, parallel execution, performance regression alerts, and a comprehensive reporting system.
- **Phase 4 (Weeks 10-12): Polish & Documentation**: Finalize all documentation, optimize performance, and explore advanced testing paradigms (BDD, KDD).
