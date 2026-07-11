#include "../include/ElementBufferObject.hpp"
#include "../glad/glad.h"
#include <cstddef>

void ElementBufferObject::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,GLID);
}

void ElementBufferObject::UnBind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void ElementBufferObject::ExportData(void* Data,size_t Size,GLenum TypeDraw){
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Data,TypeDraw);
}

void ElementBufferObject::Clear(){
    UnBind();
    glDeleteBuffers(1,&GLID);
}

unsigned int ElementBufferObject::getGLID(){
    return GLID;
}

ElementBufferObject::ElementBufferObject(){
    glGenBuffers(1,&GLID);
    Bind();
}

ElementBufferObject::~ElementBufferObject(){
    Clear();
}