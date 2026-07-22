#include "../../include/Graphic/ElementBufferObject.hpp"
#include "../../glad/glad.h"
#include <cstddef>

void Phantom::Graphic::ElementBufferObject::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GLID);
}

void Phantom::Graphic::ElementBufferObject::UnBind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Phantom::Graphic::ElementBufferObject::ExportData(void *Data, size_t Size,
                                                       GLenum TypeDraw) {
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Data, TypeDraw);
}

void Phantom::Graphic::ElementBufferObject::Clear() {
  UnBind();
  glDeleteBuffers(1, &GLID);
}

unsigned int Phantom::Graphic::ElementBufferObject::getGLID() { return GLID; }

Phantom::Graphic::ElementBufferObject::ElementBufferObject() {
  glGenBuffers(1, &GLID);
  Bind();
}

Phantom::Graphic::ElementBufferObject::~ElementBufferObject() { Clear(); }