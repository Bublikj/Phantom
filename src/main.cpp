#include "../glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>  // Для вывода ошибок
#include "../include/VertexBufferObject.hpp"
#include "../include/VertexArrayObject.hpp"
#include "../include/ElementBufferObject.hpp"
#include "../include/Shader.hpp"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

void CallBackResizeWindow(GLFWwindow *window,int width,int height){
    glViewport(0,0,width, height);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // ✅ Настройка версии OpenGL (важно!)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // ✅ ИНИЦИАЛИЗИРУЕМ GLAD!
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
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

    int  success;

    char infoLog[512];
    
    
    VertexBufferObject VBO;
    VertexArrayObject VAO;
    ElementBufferObject EBO;
    
    VBO.ExportData(vertices,sizeof(vertices),GL_STATIC_DRAW);
    EBO.ExportData(indices,sizeof(indices));

    VAO.setVertexAttribute(0,3, 3 * sizeof(float),(void*)0);


    Shader shader("../shaders/default.glsl");
    
    glfwSetWindowSizeCallback(window,CallBackResizeWindow);
    shader.Using();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        // ✅ Теперь glClear работает!
        glClearColor(22.f/255, 22.f/255, 22.f/255,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.setFloat("iTime",glfwGetTime());
        shader.Using();
        
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        VAO.Unbind();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.UnUsing();

    //shader.Clear();
    //VBO.Clear();
    //VAO.Clear();
    //EBO.Clear();
    glfwTerminate();
    return 0;
}