cmake_minimum_required(VERSION 3.10)
project(Phantom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(libs/glad/include)

# Явно перечисляем все исходники
set(SOURCES
    
    src/main.cpp
    glad/glad.c
    src/Graphic/VertexBufferObject.cpp
    src/Graphic/VertexArrayObject.cpp
    src/Graphic/ElementBufferObject.cpp
    src/Core/GLSLParser.cpp
    src/Graphic/Shader.cpp
    src/Core/Window.cpp
    src/Core/MainApplication.cpp
    src/Graphic/RenderContext.cpp
    # Добавьте все ваши .cpp файлы
)

add_executable(phantom ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(phantom
    ${OPENGL_LIBRARIES}
    glfw
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)