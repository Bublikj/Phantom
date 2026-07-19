#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"
namespace Phantom {
class Mesh{

public:

private:
    VertexArrayObject VAO;
    VertexBufferObject VBO;
    ElementBufferObject EBO;
};
}