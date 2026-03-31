cmake_minimum_required(VERSION 3.10)
project(N_Body VERSION 1.0)

# Imposta lo standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Aggiunge la cartella include per gli header file
include_directories(include)

# Crea l'eseguibile compilando il main.cpp
add_executable(N_Body source/main.cpp source/Pianeta.cpp source/EulerIntegrator.cpp source/SolarSystem.cpp source/Reader.cpp)
# target_include_directories(N_Body PRIVATE include)

find_package(Python3 COMPONENTS Development NumPy REQUIRED)
target_link_libraries(N_Body PRIVATE Python3::NumPy Python3::Python)
