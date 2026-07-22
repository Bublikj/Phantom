#pragma once
#include <string>
#include "../../glad/glad.h"
namespace Phantom {
class Shader{
public:
    Shader(const std::string &path);
    Shader();
    ~Shader();

    void Setup(const std::string &path);
    
    void Clear();
    
    void Using();
    void UnUsing();

    void setBool(const std::string &name,bool value);
    void setVec2Bool(const std::string &name,bool x,bool y);
    void setVec3Bool(const std::string &name,bool x,bool y,bool z);
    void setVec4Bool(const std::string &name,bool x,bool y,bool z,bool w);

    void setInt(const std::string &name,int value);
    void setVec2Int(const std::string &name,int x,int y);
    void setVec3Int(const std::string &name,int x,int y,int z);
    void setVec4Int(const std::string &name,int x,int y,int z,int w);
    
    void setUInt(const std::string &name,unsigned int value);
    void setVec2UInt(const std::string &name,unsigned int x,unsigned int y);
    void setVec3UInt(const std::string &name,unsigned int x,unsigned int y,unsigned int z);
    void setVec4UInt(const std::string &name,unsigned int x,unsigned int y,unsigned int z,unsigned int w);

    void setFloat(const std::string &name,float value);
    void setVec2Float(const std::string &name,float x,float y);
    void setVec3Float(const std::string &name,float x,float y,float z);
    void setVec4Float(const std::string &name,float x,float y,float z,float w);

    void setDouble(const std::string &name,double value);
    void setVec2Double(const std::string &name,double x,double y);
    void setVec3Double(const std::string &name,double x,double y,double z);
    void setVec4Double(const std::string &name,double x,double y,double z,double w);
    
    unsigned int getID();
private:
    unsigned int ProgramId=0;   
    unsigned int CompileShader(const char* source,GLenum TypeShader);
    unsigned int CreateProgram(unsigned int FragShader,unsigned int VertShader);
};
}