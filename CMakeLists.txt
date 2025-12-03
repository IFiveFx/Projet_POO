Cmake_minimum_required(VERSION 3.10)
project("PROJET_POO")

# Utilise C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Use target-based includes: project headers for `exe` and rely on the
# `nfd` target to export its include directories (PUBLIC include/).
# Remove global include_directories to avoid polluting global include path.


# Récupère tous les fichiers .cpp dans src/
file(GLOB SOURCES "src/*.cpp")

# Crée l'exécutable
add_executable(exe ${SOURCES})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_subdirectory(./nativefiledialog-extended)
target_include_directories(exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(exe PRIVATE nfd)

if (SFML_FOUND)
    # Some SFML CMake packages provide imported targets (SFML::Graphics),
    # others only expose library names. Try imported targets first, fallback
    # to plain library names if they are not available.
    if (TARGET SFML::Graphics)
        target_link_libraries(exe PRIVATE SFML::Graphics SFML::Window SFML::System)
    else()
        target_link_libraries(exe PRIVATE sfml-graphics sfml-window sfml-system)
    endif()
else()
    message(FATAL_ERROR "SFML not found. Install SFML development packages or set SFML_DIR.")
endif()
