cmake_minimum_required(VERSION 3.10)
project(PROJET_POO)

# Utiliser C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Récupérer tous les fichiers .cpp dans src/
file(GLOB SOURCES "src/*.cpp")

# Créer l’exécutable
add_executable(exe ${SOURCES})

# Inclure les headers du projet
target_include_directories(exe PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Ajouter nativefiledialog
add_subdirectory(nativefiledialog-extended)
target_link_libraries(exe PRIVATE nfd)

# Linux spécifique : s’assurer que GTK3 est trouvé
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    target_include_directories(exe PRIVATE ${GTK3_INCLUDE_DIRS})
    target_link_libraries(exe PRIVATE ${GTK3_LIBRARIES})
    add_definitions(${GTK3_CFLAGS_OTHER})
endif()

# Windows spécifique : link des bibliothèques système
if(WIN32)
    target_link_libraries(exe PRIVATE ole32 uuid shell32)
endif()

# Ajouter SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
if(SFML_FOUND)
    if(TARGET SFML::Graphics)
        target_link_libraries(exe PRIVATE SFML::Graphics SFML::Window SFML::System)
    else()
        target_link_libraries(exe PRIVATE sfml-graphics sfml-window sfml-system)
    endif()
else()
    message(FATAL_ERROR "SFML not found. Install SFML development packages or set SFML_DIR.")
endif()
