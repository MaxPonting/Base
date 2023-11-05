#version 330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec2 aTextureCoordinates;

out vec2 vTextureCoordinates;

void main()
{   
    gl_Position = aPosition; 
    vTextureCoordinates = aTextureCoordinates;
}