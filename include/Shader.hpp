#include <string>

class Shader{
public:
    Shader(const char* PathGLSLShader);
    Shader();
    
    void Setup(const char* PathGLSLShader);
        
    void Clear();
    
    void Using();
    void UnUsing();

    void setInt(const std::string &name,int value);
    void setFloat(const std::string &name,float value);
    void setBool(const std::string &name,bool value);
    void setDouble(const std::string &name,double value);

    unsigned int getID();
private:
    unsigned int ProgramId=0;
};