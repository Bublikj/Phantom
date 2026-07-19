
#include "../glad/glad.h"
#include <cstddef> // для size_t
namespace Phantom {

class VertexBufferObject{
public:
    VertexBufferObject();
    ~VertexBufferObject();
    void Bind();
    unsigned int getGLID();
    void UnBind();
    void Clear();
    void ExportData(void* Data,size_t Size,GLenum TypeDraw=GL_STATIC_DRAW);
private:
    unsigned int GLID;
};
}