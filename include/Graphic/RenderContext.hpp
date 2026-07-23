#include "Shader.hpp"
#include "VertexArrayObject.hpp"
namespace Phantom {

namespace Graphic {
enum TypeDrawing { Elements, Arrays };
class RenderContext{

public:
  RenderContext();
  void Draw(Phantom::Graphic::VertexArrayObject &VAO,unsigned int count,Phantom::Graphic::Shader &Shader,TypeDrawing RenderMethod, GLenum TypeDraw=GL_TRIANGLES, GLenum TypeData=GL_UNSIGNED_INT);
  void ClearColor(float r, float g, float b, float a = 1.0);
  
};

}
}