#include <GLFW/glfw3.h>
#include <string>
namespace Phantom {
class Window{
public:
    Window(int width,int height,std::string title);
    void Destroy();
    int  ShouldClose();
    void SwapBuffers();
    void PollEvents();
    
    void setCallbackSizeWindow(GLFWwindowsizefun callback);
    void setTitleWindow(std::string title);
    
    void getSizeWindow(int *width,int *height);
    void getPositionMouseWindow(double *x,double *y);
    void makeContext();
    void IntiGL();
    void clearBackround(float r,float g,float b,float a=1.0);

    int  getKey(int hotkey);
    std::string getTitleWindow();
    double getDeltaTime();

private:
    GLFWwindow* m_window;
};
}