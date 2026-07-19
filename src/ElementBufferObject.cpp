#include "../include/ElementBufferObject.hpp"
#include "../glad/glad.h"
#include <cstddef>

void Phantom::ElementBufferObject::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,GLID);
}

void Phantom::ElementBufferObject::UnBind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Phantom::ElementBufferObject::ExportData(void *Data, size_t Size,
                                              GLenum TypeDraw) {
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Data, TypeDraw);
}

void Phantom::ElementBufferObject::Clear() {
  UnBind();
  glDeleteBuffers(1, &GLID);
}

unsigned int Phantom::ElementBufferObject::getGLID() { return GLID; }

Phantom::ElementBufferObject::ElementBufferObject() {
  glGenBuffers(1, &GLID);
  Bind();
}

Phantom::ElementBufferObject::~ElementBufferObject() { Clear(); }