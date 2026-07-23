#include "../../include/Graphic/RenderContext.hpp"

Phantom::Graphic::RenderContext::RenderContext(){}



void Phantom::Graphic::RenderContext::ClearColor(float r,float g,float b,float a){
    glClearColor(r,g,b,a);
}

void Phantom::Graphic::RenderContext::Draw(Phantom::Graphic::VertexArrayObject &VAO,unsigned int count,Phantom::Graphic::Shader &Shader,TypeDrawing MethodRender,GLenum TypeDraw, GLenum TypeData){

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