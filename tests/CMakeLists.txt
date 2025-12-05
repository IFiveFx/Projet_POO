# CMake config for tests using Catch2
# This file expects to be included from the root CMake project

include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(catch2)

find_package(OpenMP)

enable_testing()

# Create a small static library with the project core sources needed by tests
add_library(project_core STATIC
    ${CMAKE_SOURCE_DIR}/src/Cell.cpp
    ${CMAKE_SOURCE_DIR}/src/GameRules.cpp
    ${CMAKE_SOURCE_DIR}/src/calculsAlive.cpp
    ${CMAKE_SOURCE_DIR}/src/calculsDead.cpp
    ${CMAKE_SOURCE_DIR}/src/Grid.cpp
    ${CMAKE_SOURCE_DIR}/src/file.cpp
)

target_include_directories(project_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
if(OpenMP_CXX_FOUND)
    target_link_libraries(project_core PUBLIC OpenMP::OpenMP_CXX)
endif()

# Test executable
add_executable(tests
    test_gamerules.cpp
    test_cell.cpp
    test_grid.cpp
)

target_link_libraries(tests PRIVATE project_core Catch2::Catch2WithMain)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
# Ensure Catch2 headers are visible to the tests target (FetchContent provides catch2_SOURCE_DIR)
if(DEFINED catch2_SOURCE_DIR)
    target_include_directories(tests PRIVATE ${catch2_SOURCE_DIR}/src)
endif()

include(Catch)
catch_discover_tests(tests)
