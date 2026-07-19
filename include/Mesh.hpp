#pragma once
#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"
#include <vector>

namespace Phantom{

class Mesh {
private:
  // Буферы
  Phantom::VertexArrayObject VAO;
  Phantom::VertexBufferObject VBO;
  Phantom::ElementBufferObject EBO;

  // Данные
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  // Параметры
  bool hasIndices;
  GLenum drawMode; // GL_TRIANGLES, GL_LINES, GL_POINTS и т.д.

  void SetupMesh();

public:
  Mesh();
  Mesh(const std::vector<float> &vertices,const std::vector<unsigned int> &indices);
  Mesh(const std::vector<float> &vertices); // Без индексов (glDrawArrays)

  ~Mesh();

  void Draw();
  void Draw(unsigned int count);

  // Геттеры
  const std::vector<float> &GetVertices() const { return vertices; }
  const std::vector<unsigned int> &GetIndices() const { return indices; }

  // Сеттеры
  void SetVertices(const std::vector<float> &newVertices);
  void SetIndices(const std::vector<unsigned int> &newIndices);
  void SetDrawMode(GLenum mode) { drawMode = mode; }

  // Очистка
  void Clear();
};

}