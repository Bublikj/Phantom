#include "../glad/glad.h"
#include <cstddef>

class VertexArrayObject{
public:
    unsigned int getGLID();
    void Bind();
    void Unbind();
    void Clear();
    void setVertexAttribute(unsigned int Index,unsigned int Size,size_t Stride,const void* Pointer,GLenum TypeData=GL_FLOAT,GLenum Normalized=GL_FALSE);
    VertexArrayObject();
    ~VertexArrayObject();
private:
    unsigned int GLID;
};