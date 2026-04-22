cmake_minimum_required(VERSION 3.10)
project(N_Body VERSION 1.0)

# Imposta lo standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Aggiunge la cartella include per gli header file
include_directories(include)

#GTest 
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/d72f9c8aea6817cdf1ca0ac10887f328de7f3da2.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Crea l'eseguibile compilando il main.cpp
add_executable(N_Body source/main.cpp source/Planet.cpp source/EulerIntegrator.cpp source/SolarSystem.cpp source/Reader.cpp)
# target_include_directories(N_Body PRIVATE include)

find_package(Python3 COMPONENTS Development NumPy REQUIRED)
target_link_libraries(N_Body PRIVATE Python3::NumPy Python3::Python)

enable_testing()

add_executable(
  hello_test
  hello_test.cc
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)