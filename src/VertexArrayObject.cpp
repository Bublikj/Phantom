#include "../include/VertexArrayObject.hpp"
#include "../glad/glad.h"

void Phantom::VertexArrayObject::Bind() { glBindVertexArray(GLID); }

void Phantom::VertexArrayObject::Unbind() { glBindVertexArray(0); }

void Phantom::VertexArrayObject::Clear() {
  Unbind();
  glDeleteVertexArrays(1, &GLID);
}

unsigned int Phantom::VertexArrayObject::getGLID() { return GLID; }

Phantom::VertexArrayObject::VertexArrayObject() {
  glGenVertexArrays(1, &GLID);
  Bind();
}

Phantom::VertexArrayObject::~VertexArrayObject() { Clear(); }

void Phantom::VertexArrayObject::setVertexAttribute(
    unsigned int Index, unsigned int Size, size_t Stride, const void *Pointer,
    GLenum TypeData, GLenum Normalized) {
  Bind();
  glVertexAttribPointer(Index, Size, TypeData, Normalized, Stride, Pointer);
  glEnableVertexAttribArray(Index);
};

void Phantom::VertexArrayObject::DrawElements(unsigned int elements,
                                              GLenum TypeDraw, GLenum TypeData,
                                              const void *pointer) {
  glDrawElements(TypeDraw, elements, TypeData, pointer);
}

void Phantom::VertexArrayObject::DrawArrays(unsigned int count, int first,GLenum TypeDraw){
  glDrawArrays(TypeDraw, 0, count);
}