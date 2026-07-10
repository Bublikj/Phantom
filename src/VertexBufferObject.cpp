#include "../include/VertexBufferObject.hpp"
#include "../glad/glad.h"
#include <cstddef>

void VertexBufferObject::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER,GLID);
}

void VertexBufferObject::UnBind(){
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VertexBufferObject::ExportData(void* Data,size_t Size,GLenum TypeDraw){
    Bind();
    glBufferData(GL_ARRAY_BUFFER, Size, Data,TypeDraw);
}

void VertexBufferObject::Clear(){
    UnBind();
    glDeleteBuffers(1,&GLID);
}

unsigned int VertexBufferObject::getGLID(){
    return GLID;
}

VertexBufferObject::VertexBufferObject(){
    glGenBuffers(1,&GLID);
    Bind();
}

VertexBufferObject::~VertexBufferObject(){
    Clear();
}