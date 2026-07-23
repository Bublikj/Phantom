#include "../../include/Core/MainApplication.hpp"
#include "../../glad/glad.h"
#include "../../include/Core/Window.hpp"
#include "../../include/Graphic/ElementBufferObject.hpp"
#include "../../include/Graphic/Shader.hpp"
#include "../../include/Graphic/VertexArrayObject.hpp"
#include "../../include/Graphic/RenderContext.hpp"
#include "../../include/Graphic/VertexBufferObject.hpp"

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
  Phantom::Graphic::RenderContext renderer;

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    window.Destroy();
    return -1;
  }

  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


  std::vector<float> Vertices = {
      1.0f,  1.0f,  0.0f,
      1.0f,  -1.0f, 0.0f, 
      -1.0f, -1.0f, 0.0f,
      -1.0f, 1.0f,  0.0f  
  };

  std::vector<unsigned int> Indices = {
      0, 1, 3, 
      1, 2, 3  
  };

  Phantom::Graphic::VertexArrayObject VAO;
  Phantom::Graphic::VertexBufferObject VBO;
  Phantom::Graphic::ElementBufferObject EBO;

  VAO.Bind();

  VBO.Bind();
  VBO.ExportData(Vertices.data(),
                 Vertices.size() * sizeof(float), 
                 GL_STATIC_DRAW);

  VAO.setVertexAttribute(0,                 
                         3,                
                         3 * sizeof(float), 
                         (void *)0 
  );

  EBO.Bind();
  EBO.ExportData(Indices.data(),
                 Indices.size() * sizeof(unsigned int) // ← ПРАВИЛЬНЫЙ РАЗМЕР!
  );

  VAO.Unbind();

  Phantom::Graphic::Shader shader("../shaders/default.glsl");
  window.setCallbackSizeWindow(CallBackResizeWindow);
  shader.Using();

  while (!window.ShouldClose()) {

    renderer.ClearColor(22.f / 255, 22.f / 255, 22.f / 255, 1.0f);
    renderer.ClearDepth();

    shader.setFloat("iTime", glfwGetTime());
    renderer.DrawVAO(VAO,6,shader,Phantom::Graphic::TypeDrawing::Elements);

    //VAO.Bind();
    //VAO.DrawElements(6); // 6 индексов (2 треугольника × 3 вершины)
    //VAO.Unbind();

    window.SwapBuffers();
    window.PollEvents();
  }

  shader.UnUsing();
  window.Destroy();
  return 0;
}