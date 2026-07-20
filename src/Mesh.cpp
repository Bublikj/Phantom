// Mesh.cpp
#include "../include/Mesh.hpp"

Phantom::Mesh::Mesh() : hasIndices(false), drawMode(GL_TRIANGLES) {
}

Phantom::Mesh::Mesh(const std::vector<float> &vertices,
                    const std::vector<unsigned int> &indices)
    : vertices(vertices), indices(indices), hasIndices(true),
      drawMode(GL_TRIANGLES) {
  SetupMesh();
}

Phantom::Mesh::Mesh(const std::vector<float> &vertices)
    : vertices(vertices), hasIndices(false), drawMode(GL_TRIANGLES) {
  SetupMesh();
}

Phantom::Mesh::~Mesh() { Clear(); }

void Phantom::Mesh::SetupMesh() {
  // Привязываем VAO
  VAO.Bind();

  // Загружаем вершины в VBO
  VBO.Bind();
  VBO.ExportData(vertices.data(), vertices.size() * sizeof(float));

  // Загружаем индексы в EBO (если есть)
  if (hasIndices && !indices.empty()) {
    EBO.Bind();
    EBO.ExportData(indices.data(), indices.size() * sizeof(unsigned int));
  }

  // Настраиваем атрибуты вершин
  // Предполагаем: x, y, z, (но можно сделать гибко)
  VAO.setVertexAttribute(0, 3, 3 * sizeof(float), 0);

  // Отвязываем
  VBO.UnBind();
  VAO.Unbind();
}

void Phantom::Mesh::Draw() {
  VAO.Bind();

  if (hasIndices && !indices.empty()) {
    VAO.DrawElements(indices.size(),drawMode,GL_UNSIGNED_INT,0);
} else {
    VAO.DrawArrays(vertices.size()/3,0,drawMode);
  }

  VAO.Unbind();
}

void Phantom::Mesh::Draw(unsigned int count) {
  VAO.Bind();

  if (hasIndices && !indices.empty()) {
    VAO.DrawElements(count,drawMode);
  } else {
    VAO.DrawArrays(count,0,drawMode);
  }

  VAO.Unbind();
}

void Phantom::Mesh::SetVertices(const std::vector<float> &newVertices) {
  vertices = newVertices;
  SetupMesh(); // Перезагружаем данные
}

void Phantom::Mesh::SetIndices(const std::vector<unsigned int> &newIndices) {
  indices = newIndices;
  hasIndices = !indices.empty();
  SetupMesh(); // Перезагружаем данные
}

void Phantom::Mesh::Clear() {
  VAO.Clear();
  VBO.Clear();
  EBO.Clear();
}