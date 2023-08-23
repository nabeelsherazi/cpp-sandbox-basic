cmake_minimum_required(VERSION 3.14)

project(
    pi-estimator
    VERSION 1.0.0
    DESCRIPTION "Estimate pi using the Monte Carlo method"
    HOMEPAGE_URL "https://example.com"
    LANGUAGES CXX
)

# Declare executable

add_executable(pi-estimator_exe source/main.cpp source/estimator.cpp)
add_executable(pi-estimator::exe ALIAS pi-estimator_exe)

set_property(TARGET pi-estimator_exe PROPERTY OUTPUT_NAME pi-estimator)

# Set C++ standard

target_compile_features(pi-estimator_exe PRIVATE cxx_std_17)

# Add include directories

target_include_directories(pi-estimator_exe PRIVATE include)

# Find dependencies

find_package(fmt REQUIRED)

# Link dependencies

target_link_libraries(pi-estimator_exe PRIVATE fmt::fmt pthread)