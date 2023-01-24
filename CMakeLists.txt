cmake_minimum_required(VERSION 3.24.0)

# Fetch vcpkg
include(FetchContent)
FetchContent_Declare(
    vcpkg
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG 2022.11.14)
FetchContent_GetProperties(vcpkg)
if(NOT vcpkg_POPULATED)
    FetchContent_Populate(vcpkg)
    set(CMAKE_TOOLCHAIN_FILE
        "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

# Build project
project(
    VirtualDrivingLab
    VERSION 0.1.0
    LANGUAGES CXX)

option(VirtualDrivingLab_BUILD_DOCS "Build the docs" ${PROJECT_IS_TOP_LEVEL})
option(VirtualDrivingLab_BUILD_TESTS "Build the tests" ${PROJECT_IS_TOP_LEVEL})

add_subdirectory(src)

# Build docs
if(VirtualDrivingLab_BUILD_DOCS)
    add_subdirectory(docs)
endif()

# Build tests
if(VirtualDrivingLab_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
