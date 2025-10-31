cmake_minimum_required(VERSION 3.16)

project(libopensteamschema LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(LIBOPENSTEAMSCHEMA_BUILD_TESTS "Build tests" OFF)

add_subdirectory(src)

if(LIBOPENSTEAMSCHEMA_BUILD_TESTS)
    enable_testing()
    add_subdirectory(third_party/unity EXCLUDE_FROM_ALL)
    add_subdirectory(tests)
endif()
