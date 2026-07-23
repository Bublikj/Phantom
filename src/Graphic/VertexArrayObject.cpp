#include "../../glad/glad.h"
#include "../../include/Graphic/VertexArrayObject.hpp"

void Phantom::Graphic::VertexArrayObject::Bind() { glBindVertexArray(GLID); }

void Phantom::Graphic::VertexArrayObject::Unbind() { glBindVertexArray(0); }

void Phantom::Graphic::VertexArrayObject::Clear() {
  Unbind();
  glDeleteVertexArrays(1, &GLID);
}

unsigned int Phantom::Graphic::VertexArrayObject::getGLID() { return GLID; }

Phantom::Graphic::VertexArrayObject::VertexArrayObject() {
  glGenVertexArrays(1, &GLID);
}

Phantom::Graphic::VertexArrayObject::~VertexArrayObject() { Clear(); }

void Phantom::Graphic::VertexArrayObject::setVertexAttribute(
    unsigned int Index, unsigned int Size, size_t Stride, const void *Pointer,
    GLenum TypeData, GLenum Normalized) {
  Bind();
  glVertexAttribPointer(Index, Size, TypeData, Normalized, Stride, Pointer);
  glEnableVertexAttribArray(Index);
};

void Phantom::Graphic::VertexArrayObject::DrawElements(unsigned int elements,
                                                       GLenum TypeDraw,
                                                       GLenum TypeData,
                                                       const void *pointer) {
  glDrawElements(TypeDraw, elements, TypeData, pointer);
}

void Phantom::Graphic::VertexArrayObject::DrawArrays(unsigned int count,
                                                     int first,
                                                     GLenum TypeDraw) {
  glDrawArrays(TypeDraw, 0, count);
}