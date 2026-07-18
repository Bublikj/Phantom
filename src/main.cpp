#include "../glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>  // Для вывода ошибок
#include "../include/VertexBufferObject.hpp"
#include "../include/VertexArrayObject.hpp"
#include "../include/ElementBufferObject.hpp"
#include "../include/Shader.hpp"
#include "../include/Window.hpp"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

void CallBackResizeWindow(GLFWwindow *window,int width,int height){
    glViewport(0,0,width, height);
}

void InitGL(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int main(void)
{
    if (!glfwInit())
        return -1;
    
    InitGL();
    
    Window window(SCR_WIDTH,SCR_HEIGHT,"Phantom");

    /* Initialize the library */
    
    /* Create a windowed mode window and its OpenGL context */
    window.makeContext();

    // ✅ ИНИЦИАЛИЗИРУЕМ GLAD!
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        window.Destroy();
        return -1;
    }

    // ✅ Теперь можно использовать OpenGL функции!
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);

    
    
    float vertices[] = {
        // first triangle
     1.0f,  1.0f, 0.0f,  // top right
     1.0f, -1.0f, 0.0f,  // bottom right
    -1.0f, -1.0f, 0.0f,  // bottom left
    -1.0f,  1.0f, 0.0f // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };  
    
    VertexBufferObject VBO;
    VertexArrayObject VAO;
    ElementBufferObject EBO;
    
    VBO.ExportData(vertices,sizeof(vertices),GL_STATIC_DRAW);
    EBO.ExportData(indices,sizeof(indices));

    VAO.setVertexAttribute(0,3, 3 * sizeof(float),(void*)0);

    Shader shader("../shaders/default.glsl");
    
    window.setCallbackSizeWindow(CallBackResizeWindow);
    shader.Using();
    /* Loop until the user closes the window */
    while (!window.ShouldClose())
    {
        /* Render here */
        // ✅ Теперь 
        // glClear работает!
        window.clearBackround(22.f/255, 22.f/255, 22.f/255,1.0f);

        shader.setFloat("iTime",glfwGetTime());
        shader.Using();
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        VAO.Unbind();
        /* Swap front and back buffers */
        window.SwapBuffers();
        /* Poll for and process events */
        window.PollEvents();
    }

    shader.UnUsing();

    //shader.Clear();
    //VBO.Clear();
    //VAO.Clear();
    //EBO.Clear();
    window.Destroy();
    return 0;
}