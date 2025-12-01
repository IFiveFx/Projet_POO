Cmake_minimum_required(VERSION 3.10)
project("PROJET_POO")

# Utilise C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajoute le dossier include/ pour les headers
include_directories(include)

# Récupère tous les fichiers .cpp dans src/
file(GLOB SOURCES "src/*.cpp")

# Crée l'exécutable
add_executable(exe ${SOURCES})