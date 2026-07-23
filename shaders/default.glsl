#version 330 core  
out vec4 FragColor;  
in vec3 Color;  

void main()  
{  
     
     FragColor = vec4(Color,1.0);  

};
//SPLIT_SHADER

#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 Color;
uniform float iTime;

void main(){
    
    gl_Position = vec4(aPos.x*sin(iTime), aPos.y*sin(iTime),aPos.z*sin(iTime), 0.25);
    Color=aPos;

};