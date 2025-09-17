# Game Engine Test Automation Framework (GETAF)

## 1. Project Vision

This project aims to develop a comprehensive, production-ready test automation framework for 3D games built with Unreal Engine 5. It serves as a portfolio piece to demonstrate enterprise-level testing practices, CI/CD integration, and technical leadership in game development quality assurance.

## 2. The Problem

Game development teams often face challenges with:
- Manual testing bottlenecks in complex 3D environments.
- Inconsistent quality assurance across build iterations.
- Difficulty in detecting performance regressions in game engines.
- Integration challenges between testing tools and game engines.
- A lack of comprehensive metrics and reporting for stakeholders.

## 3. The Solution

GETAF is a unified test automation platform designed to address these challenges by providing:
- A **multi-language test framework** integrating C++ and C#.
- **Native UE5 automation** using the Gauntlet framework.
- A comprehensive **test pyramid** implementation (Unit, Integration, System).
- **Real-time performance monitoring** and regression detection.
- **Data-driven testing** capabilities using XML/JSON configurations.
- Full **CI/CD integration** with automated quality gates using GitHub Actions.

## 4. Key Features

- **Multi-Layer Testing:** A complete testing pyramid with clear separation between Unit, Integration, and System tests.
- **Cross-Language Integration:** A C++ core framework with a C# wrapper for flexible test scripting.
- **Data-Driven Execution:** Drive test scenarios and parameters from external XML/JSON files.
- **UE5 Native Automation:** Leverage UE5's built-in automation for functional, performance, and visual testing (screenshot comparison).
- **Performance Monitoring:** Track FPS, memory usage, and other metrics in real-time to detect performance regressions automatically.
- **API & Database Testing:** Includes modules for testing REST APIs and validating database integrity.

## 5. Technology Stack

### Core Stack
- **Game Engine**: Unreal Engine 5
- **Primary IDE**: Visual Studio Community 2022
- **Version Control & CI/CD**: Git / GitHub / GitHub Actions
- **C++ Testing**: GoogleTest
- **C# Testing**: NUnit
- **Database**: MySQL Community Server
- **API Testing**: Postman (for manual testing), C++ HTTP Client (for automation)

### Supporting Tools
- **Build System**: CMake
- **Scripting**: Python, PowerShell

## 6. Project Structure

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

## 7. Getting Started

1.  **Install Core Tools**:
    *   Visual Studio Community 2022 (with C++, .NET, and Game Development workloads)
    *   Unreal Engine 5
    *   Git, MySQL Community Server, Postman, and Python 3.11+.
2.  **Clone the repository**.
3.  **Set up the Database** using the scripts in the `Database/` directory.
4.  **Build the project** using the provided CMake configuration.

## 8. Project Roadmap

The project is structured in a 12-week plan:

-   **Weeks 1-3: Core Framework Development**: Build the foundational C++ test framework, C# integration layer, and basic CI/CD pipeline.
-   **Weeks 4-6: UE5 Game Integration**: Create a simple 3D game and integrate it with UE5's native automation framework.
-   **Weeks 7-9: CI/CD and Advanced Features**: Set up a full CI/CD pipeline with GitHub Actions, implement data-driven testing, and build a performance regression detection system.
-   **Weeks 10-12: Testing Approaches & Polish**: Implement BDD/KDD approaches, finalize documentation, and prepare the project for portfolio presentation.
