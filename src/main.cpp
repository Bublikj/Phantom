#include "../glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>  // Для вывода ошибок
#include "../include/VertexBufferObject.hpp"
#include "../include/VertexArrayObject.hpp"
#include "../include/ElementBufferObject.hpp"



const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec3 Color;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "Color=aPos;"
    "}\0";

const char *fragmentShaderSource="#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 Color;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1-Color,1.0);\n"
"}\0";



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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f // top left 
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


    unsigned int FragmentShader,VertexShader;

    VertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(VertexShader);

    FragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(FragmentShader);
    
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, VertexShader);
    glAttachShader(shaderProgram, FragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;

    }

    glUseProgram(shaderProgram);

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
    
    glfwSetWindowSizeCallback(window,CallBackResizeWindow);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        // ✅ Теперь glClear работает!
        glClearColor(22.f/255, 22.f/255, 22.f/255,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram);
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        VAO.Unbind();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glUseProgram(0);

    glDeleteProgram(shaderProgram);
    VBO.Clear();
    VAO.Clear();
    EBO.Clear();
    glfwTerminate();
    return 0;
}