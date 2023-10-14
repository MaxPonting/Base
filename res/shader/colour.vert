#version 330 core

layout(location = 0) in vec4 aPosition;

uniform mat4 uView;
uniform mat4 uProjection;

void main()
{   
    gl_Position = uProjection * uView * aPosition; 
}