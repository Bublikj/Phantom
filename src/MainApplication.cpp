#include "../include/MainApplication.hpp"
#include "../glad/glad.h"
#include "../include/ElementBufferObject.hpp"
#include "../include/Shader.hpp"
#include "../include/VertexArrayObject.hpp"
#include "../include/VertexBufferObject.hpp"
#include "../include/Window.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

void CallBackResizeWindow(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void InitGL() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

int MainApplication::execute(int argc, char *argv[]) {
  if (!glfwInit())
    return -1;

  InitGL();

  Phantom::Window window(SCR_WIDTH, SCR_HEIGHT, "Phantom");
  window.makeContext();

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    window.Destroy();
    return -1;
  }

  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

  // ============================================
  // ДАННЫЕ
  // ============================================
  std::vector<float> Vertices = {
      1.0f,  1.0f,  0.0f, // 0 - правый верхний
      1.0f,  -1.0f, 0.0f, // 1 - правый нижний
      -1.0f, -1.0f, 0.0f, // 2 - левый нижний
      -1.0f, 1.0f,  0.0f  // 3 - левый верхний
  };

  std::vector<unsigned int> Indices = {
      0, 1, 3, // первый треугольник
      1, 2, 3  // второй треугольник
  };

  // ============================================
  // СОЗДАНИЕ БУФЕРОВ
  // ============================================
  Phantom::Graphic::VertexArrayObject VAO;
  Phantom::Graphic::VertexBufferObject VBO;
  Phantom::Graphic::ElementBufferObject EBO;

  // ✅ 1. Привязываем VAO (ЭТО ВАЖНО!)
  VAO.Bind();

  // ✅ 2. Загружаем вершины в VBO
  VBO.Bind();
  VBO.ExportData(Vertices.data(),
                 Vertices.size() * sizeof(float), // ← ПРАВИЛЬНЫЙ РАЗМЕР!
                 GL_STATIC_DRAW);

  // ✅ 3. Настраиваем атрибут вершины
  VAO.setVertexAttribute(0,                 // location
                         3,                 // размер (x, y, z)
                         3 * sizeof(float), // stride
                         (void *)0          // offset
  );

  // ✅ 4. Загружаем индексы в EBO
  EBO.Bind();
  EBO.ExportData(Indices.data(),
                 Indices.size() * sizeof(unsigned int) // ← ПРАВИЛЬНЫЙ РАЗМЕР!
  );

  // ✅ 5. Отвязываем VAO (но EBO остаётся привязан к VAO)
  VAO.Unbind();

  // ============================================
  // ШЕЙДЕР
  // ============================================
  Phantom::Shader shader("../shaders/default.glsl");
  window.setCallbackSizeWindow(CallBackResizeWindow);

  shader.Using();

  // ============================================
  // ИГРОВОЙ ЦИКЛ
  // ============================================
  while (!window.ShouldClose()) {

    window.clearBackround(22.f / 255, 22.f / 255, 22.f / 255, 1.0f);

    shader.setFloat("iTime", glfwGetTime());
    // ✅ НЕ ВЫЗЫВАЙТЕ shader.Using() повторно, если уже вызвали!

    VAO.Bind();
    VAO.DrawElements(6); // 6 индексов (2 треугольника × 3 вершины)
    VAO.Unbind();

    window.SwapBuffers();
    window.PollEvents();
  }

  shader.UnUsing();
  window.Destroy();
  return 0;
}