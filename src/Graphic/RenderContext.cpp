#include "../../include/Graphic/RenderContext.hpp"

Phantom::Graphic::RenderContext::RenderContext(){}

void Phantom::Graphic::RenderContext::ClearColor(float r,float g,float b,float a){
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Phantom::Graphic::RenderContext::DrawVAO(Phantom::Graphic::VertexArrayObject &VAO,unsigned int count,Phantom::Graphic::Shader &Shader,TypeDrawing MethodRender,GLenum TypeDraw, GLenum TypeData){

    if(MethodRender==Phantom::Graphic::TypeDrawing::Elements){
        VAO.Bind();
        VAO.DrawElements(count,TypeDraw,TypeData);
        VAO.Unbind();
    }else{
        VAO.Bind();
        VAO.DrawArrays(count,0);
        VAO.Unbind();
    }
}

void Phantom::Graphic::RenderContext::ClearDepth(){
  glClearDepth(GL_DEPTH_BUFFER_BIT);
}

void Phantom::Graphic::RenderContext::EnableTransparency(){
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}