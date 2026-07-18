#include "../include/Window.hpp"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <string>

Window::Window(int width,int height,std::string title){
    m_window=glfwCreateWindow(width,height,title.c_str(),NULL,NULL);
    
};

void Window::IntiGL(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::SwapBuffers(){
    glfwSwapBuffers(m_window);

};

void Window::Destroy(){
    glfwTerminate();

}

void Window::setCallbackSizeWindow(GLFWwindowsizefun callback){
    glfwSetWindowSizeCallback(m_window,callback);
};

void Window::setTitleWindow(std::string title){
    glfwSetWindowTitle(m_window,title.c_str());
};

void Window::getSizeWindow(int *width,int *height){
    glfwGetWindowSize(m_window,width,height);
};

void Window::getPositionMouseWindow(double *x,double *y){
    glfwGetCursorPos(m_window,x,y);
};

double Window::getDeltaTime(){
    return glfwGetTime();
}

void Window::clearBackround(float r,float g,float b,float a){
    glClearColor(r,g, b,a);
    glClear(GL_COLOR_BUFFER_BIT);
};

int Window::getKey(int hotkey){
    return glfwGetKey(m_window,hotkey);
};

void Window::makeContext(){
    glfwMakeContextCurrent(m_window);
};

std::string Window::getTitleWindow(){
    std::string title=glfwGetWindowTitle(m_window);
    return title;
};

void Window::PollEvents(){
    glfwPollEvents();
};


int Window::ShouldClose(){
    return glfwWindowShouldClose(m_window);
};
