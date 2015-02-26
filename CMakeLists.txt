cmake_minimum_required(VERSION 2.8)
project(raymarch_engine)

set(EXECUTABLE_NAME raymarch_engine.out)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/build/modules)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x -stdlib=libc++ -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include")

set(SOURCES
    src/objects/raymarchObject.cpp
    src/objects/camera.cpp
    src/scanner.cpp
    src/symbolTable.cpp
    src/main.cpp
    src/engine.cpp
    src/shaderAssembler.cpp
    src/shader.cpp
    src/lexer.cpp
    src/utils.cpp
    src/log.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/lib/include/fontstash)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/include/glm)
include_directories(${CMAKE_SOURCE_DIR}/lib/include/glm)
include_directories(${CMAKE_SOURCE_DIR}/lib/include/glm/gtc)

find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})

option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glfw)
include_directories(${CMAKE_SOURCE_DIR}/deps/glfw/include)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME}
    glfw ${GLFW_LIBRARIES} ${GLEW_LIBRARY})

