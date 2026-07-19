#include "../include/VertexBufferObject.hpp"
#include "../glad/glad.h"
#include <cstddef>

void Phantom::VertexBufferObject::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, GLID);
}

void Phantom::VertexBufferObject::UnBind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void Phantom::VertexBufferObject::ExportData(void *Data, size_t Size,
                                             GLenum TypeDraw) {
  Bind();
  glBufferData(GL_ARRAY_BUFFER, Size, Data, TypeDraw);
}

void Phantom::VertexBufferObject::Clear() {
  UnBind();
  glDeleteBuffers(1, &GLID);
}

unsigned int Phantom::VertexBufferObject::getGLID() { return GLID; }

Phantom::VertexBufferObject::VertexBufferObject() {
  glGenBuffers(1, &GLID);
  Bind();
}

Phantom::VertexBufferObject::~VertexBufferObject() { Clear(); }