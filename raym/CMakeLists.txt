cmake_minimum_required(VERSION 2.8)
project(raym)

option(BUILD_TESTS "Build unit tests" ON)

set(SOURCE_DIR src)
set(LIB_TYPE STATIC)
set(LIB_NAME raym)

file(GLOB_RECURSE FOUND_SOURCES ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE FOUND_HEADERS ${SOURCE_DIR}/*.h)

set(INCLUDE_DIRS "")
foreach(_headerFile ${FOUND_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
        list(APPEND INCLUDE_DIRS ${_dir})
    endforeach()
set(RAYM_INCLUDE_DIRS ${INCLUDE_DIRS} CACHE INTERNAL "include directories" FORCE)

add_library(${LIB_NAME} ${LIB_TYPE} ${FOUND_SOURCES} ${FOUND_HEADERS})

if(BUILD_TESTS)
    message(STATUS "Unit tests build")

    include_directories(${RAYM_INCLUDE_DIRS})
    include_directories(tests/catch)

    file(GLOB TEST_SOURCES tests/unit/*.cpp)

    foreach(_src_file_path ${TEST_SOURCES})
        string(REPLACE ".cpp" "" test_case ${_src_file_path})
        string(REGEX MATCH "([^/]*)$" test_name ${test_case})

        set(EXECUTABLE_NAME "${test_name}_test.out")

        add_executable(${EXECUTABLE_NAME} ${_src_file_path})

        target_link_libraries(${EXECUTABLE_NAME} raym)
    endforeach(_src_file_path ${TEST_SOURCES})
endif()
