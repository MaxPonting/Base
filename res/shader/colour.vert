#version 330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec2 aTextureCoordinates;
layout(location = 2) in vec4 aColour;

uniform mat4 uView;
uniform mat4 uProjection;

out vec2 vTextureCoordinates;
out vec4 vColour;

void main()
{   
    gl_Position = uProjection * uView * aPosition; 
    vTextureCoordinates = aTextureCoordinates;
    vColour = aColour;
}