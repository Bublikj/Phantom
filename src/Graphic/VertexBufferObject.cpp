#include "../../include/Graphic/VertexBufferObject.hpp"
#include "../../glad/glad.h"
#include <cstddef>

void Phantom::Graphic::VertexBufferObject::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, GLID);
}

void Phantom::Graphic::VertexBufferObject::UnBind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void Phantom::Graphic::VertexBufferObject::ExportData(void *Data, size_t Size,
                                                      GLenum TypeDraw) {
  Bind();
  glBufferData(GL_ARRAY_BUFFER, Size, Data, TypeDraw);
}

void Phantom::Graphic::VertexBufferObject::Clear() {
  UnBind();
  glDeleteBuffers(1, &GLID);
}

unsigned int Phantom::Graphic::VertexBufferObject::getGLID() { return GLID; }

Phantom::Graphic::VertexBufferObject::VertexBufferObject() {
  glGenBuffers(1, &GLID);
  Bind();
}

Phantom::Graphic::VertexBufferObject::~VertexBufferObject() { Clear(); }