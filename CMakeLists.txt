cmake_minimum_required(VERSION 3.10)
project(N_Body VERSION 1.0)

# Imposta lo standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Aggiunge la cartella include per gli header file
include_directories(include)

#GTest 


# -------------------------------------------------------------------
# 1. CORE LIBRARY
# -------------------------------------------------------------------
add_library(NBody_Core 
    source/Planet.cpp 
    source/EulerIntegrator.cpp 
    source/SolarSystem.cpp 
    source/Reader.cpp
)

# -------------------------------------------------------------------
# 2. THE MAIN EXECUTABLE 
# -------------------------------------------------------------------
add_executable(N_Body source/main.cpp)

find_package(Python3 COMPONENTS Development NumPy REQUIRED)
target_link_libraries(N_Body PRIVATE NBody_Core Python3::NumPy Python3::Python)

# -------------------------------------------------------------------
# 3. GOOGLE TEST (Fetch e Configuration)
# -------------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/d72f9c8aea6817cdf1ca0ac10887f328de7f3da2.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  nbody_tests
  tests/test_solarsystem.cpp
)
target_link_libraries(
  nbody_tests
  PRIVATE NBody_Core
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(nbody_tests)