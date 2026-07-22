#pragma once
#include "../../glad/glad.h"
#include <cstddef>
namespace Phantom {
namespace Graphic {


class VertexArrayObject{
public:
    unsigned int getGLID();
    void Bind();
    void Unbind();
    void Clear();
    void setVertexAttribute(unsigned int Index,unsigned int Size,size_t Stride,const void* Pointer,GLenum TypeData=GL_FLOAT,GLenum Normalized=GL_FALSE);
    void DrawElements(unsigned int elements,GLenum TypeDraw=GL_TRIANGLES,GLenum TypeData=GL_UNSIGNED_INT,const void* pointer=0);
    void DrawArrays(unsigned int count,int first, GLenum TypeDraw = GL_TRIANGLES);

    VertexArrayObject();
    ~VertexArrayObject();
private:
    unsigned int GLID;
};
}
}