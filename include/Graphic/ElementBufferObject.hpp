#pragma once
#include "../../glad/glad.h"
#include <cstddef> // для size_t
namespace Phantom {

namespace Graphic {


class ElementBufferObject{
public:
    ElementBufferObject();
    ~ElementBufferObject();
    void Bind();
    unsigned int getGLID();
    void UnBind();
    void Clear();
    void ExportData(void* Data,size_t Size,GLenum TypeDraw=GL_STATIC_DRAW);
private:
    unsigned int GLID;
};

};
}