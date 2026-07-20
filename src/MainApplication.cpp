#include "../glad/glad.h"
#include "../include/Shader.hpp"
#include "../include/Window.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "../include/MainApplication.hpp"
#include "../include/Mesh.hpp"
#include <vector>
#include <iostream>

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

int MainApplication::execute(int argc, char *argv[]){
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

      glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

      std::vector<float> Vertices = {1.0f,  1.0f,  0.0f,
                                    1.0f,  -1.0f, 0.0f,
                                    -1.0f, -1.0f, 0.0f,
                                      -1.0f, 1.0f,  0.0f};

      std::vector<unsigned int> Indices = {0, 1, 3, 1, 2, 3};

      Phantom::Mesh mesh(Vertices,Indices);

      Phantom::Shader shader("../shaders/default.glsl");

      window.setCallbackSizeWindow(CallBackResizeWindow);
      shader.Using();
      
      while (!window.ShouldClose()) {
        
        window.clearBackround(22.f / 255, 22.f / 255, 22.f / 255, 1.0f);

        shader.setFloat("iTime", glfwGetTime());
        shader.Using();
        
        mesh.Draw();

        window.SwapBuffers();
        window.PollEvents();

  }

    shader.UnUsing();

    // shader.Clear();
    // VBO.Clear();
    // VAO.Clear();
    // EBO.Clear();
    window.Destroy();
    return 0;
}