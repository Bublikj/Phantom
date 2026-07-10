#include "../include/VertexArrayObject.hpp"
#include "../glad/glad.h"

void VertexArrayObject::Bind(){
    glBindVertexArray(GLID);
}

void VertexArrayObject::Unbind(){
    glBindVertexArray(0);
}

void VertexArrayObject::Clear(){
    Unbind();
    glDeleteVertexArrays(1,&GLID);
}

unsigned int VertexArrayObject::getGLID(){ 
    return GLID;
}

VertexArrayObject::VertexArrayObject(){
    glGenVertexArrays(1,&GLID);
    Bind();
}

VertexArrayObject::~VertexArrayObject(){
    Clear();
}

void VertexArrayObject::setVertexAttribute(unsigned int Index,unsigned int Size,size_t Stride,const void* Pointer,GLenum TypeData,GLenum Normalized){
    Bind();
    glVertexAttribPointer(Index, Size,TypeData,Normalized,Stride,Pointer);
    glEnableVertexAttribArray(Index);
};

