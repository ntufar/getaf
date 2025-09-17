# Tasks: Game Engine Test Automation Framework (GETAF) Core Implementation

**Input**: Design documents from `/specs/001-read-the-prd/`
**Prerequisites**: plan.md, research.md, data-model.md, contracts/

## Phase 3.1: Setup
- [X] T001 Set up the root `CMakeLists.txt` for the project in `CMakeLists.txt`.
- [X] T002 Create the main directory structure: `Source`, `Scripts`, `Config`, `Database`, `CI`, `Documentation`.
- [X] T003 Set up the C++ Core Framework project in `Source/Framework/CMakeLists.txt` and integrate GoogleTest.
- [X] T004 Set up the C# Integration Layer project (.NET 6) in `Source/Tests/`.
- [X] T005 Set up the UE5 Game project in `Source/GameLogic/`.
- [X] T006 Create the database schema based on data-model.md in Database/schema.sql. (Verified with Scripts/setup_database.py)

## Phase 3.2: Tests First (TDD) ⚠️ MUST COMPLETE BEFORE 3.3
**CRITICAL: These tests MUST be written and MUST FAIL before ANY implementation**
- [X] T007 [P] Write a failing unit test for the `ConfigReader` in `Source/Tests/Framework/ConfigReader.cpp`.
- [X] T008 [P] Write a failing unit test for the `HTTPClient` in `Source/Tests/Framework/HTTPClient.cpp`.
- [X] T009 [P] Write a failing unit test for the `DBConnector` in `Source/Tests/Framework/DBConnector.cpp`.
- [X] T010 [P] Write a failing integration test for the C++/C# bridge in `Source/Tests/Integration/CSharpBridge.cs`.

## Phase 3.3: Core Implementation (ONLY after tests are failing)
- [X] T011 [P] Implement the `ConfigReader` in `Source/Framework/ConfigReader.cpp` to parse XML/JSON files.
- [X] T012 [P] Implement the `HTTPClient` in `Source/Framework/HTTPClient.cpp` for API testing.
- [X] T013 [P] Implement the `DBConnector` in `Source/Framework/DBConnector.cpp` for MySQL. (Functional implementation using mysql-connector-c++)
- [X] T014 Implement the C++/C# bridge using P/Invoke in the C# and C++ projects.
- [X] T015 Implement the simple UE5 game logic in Source/GameLogic/ (Character, Collectibles, AI, UI).

## Phase 3.4: Integration
- [X] T016 Integrate the `DBConnector` with a `TestReporter` component to store results.
- [X] T017 Integrate the C# layer with the UE5 Gauntlet automation framework.
- [X] T018 Set up a basic GitHub Actions workflow in `.github/workflows/build.yml` to build the project.

## Phase 3.5: Polish
- [ ] T019 [P] Write comprehensive unit tests for all C++ core components to achieve >80% code coverage.
- [ ] T020 [P] Implement performance monitoring (FPS, memory) in the UE5 integration.
- [ ] T021 [P] Create data-driven test examples using the `ConfigReader` and sample XML/JSON files in `Config/`.
- [ ] T022 Write documentation for using the framework in `Documentation/`.

## Dependencies
- Setup tasks (T001-T006) must be completed before all other phases.
- Test tasks (T007-T010) must be completed before Core Implementation (T011-T015).
- Core Implementation tasks should be completed before Integration (T016-T018).

## Parallel Example
```
# Launch T007-T010 together:
Task: "Write a failing unit test for the ConfigReader in Source/Tests/Framework/ConfigReader.cpp"
Task: "Write a failing unit test for the HTTPClient in Source/Tests/Framework/HTTPClient.cpp"
Task: "Write a failing unit test for the DBConnector in Source/Tests/Framework/DBConnector.cpp"
Task: "Write a failing integration test for the C++/C# bridge in Source/Tests/Integration/CSharpBridge.cs"
```
