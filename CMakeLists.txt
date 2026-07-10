cmake_minimum_required(VERSION 3.10)
project(Phantom VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем директории
include_directories(include)
include_directories(libs/glad/include)

# Автоматический поиск .cpp файлов
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Убеждаемся, что есть хотя бы один файл
list(LENGTH SOURCES SOURCES_LENGTH)
if(SOURCES_LENGTH EQUAL 0)
    message(FATAL_ERROR "No source files found in src/ directory!")
endif()

add_executable(phantom ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(phantom
    ${OPENGL_LIBRARIES}
    glfw
    ${GLAD_LIBRARY}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Found ${SOURCES_LENGTH} source files")