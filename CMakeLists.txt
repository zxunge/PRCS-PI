cmake_minimum_required(VERSION 3.25)

if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

project(PRCS-PI
        LANGUAGES CXX
        DESCRIPTION "Demonstrate how to compute the value of π in Plane Rectangular Coordinate System.")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

set(MPPP_BUILD_STATIC_LIBRARY ON)
set(MPPP_WITH_MPFR ON)

add_subdirectory(mppp)

add_executable(prcspi main.cpp)

target_link_libraries(prcspi PRIVATE mp++ mpfr gmp)
