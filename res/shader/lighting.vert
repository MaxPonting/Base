#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TextureCoordinates;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform vec2 u_TextureSize;
uniform vec2 u_SubTextureIndex;
uniform vec2 u_SubTextureSize;

out vec2 v_TextureCoordinates;

void main()
{   
    gl_Position = u_Projection * u_View * u_Model * a_Position;
    v_TextureCoordinates = ((u_SubTextureIndex + a_TextureCoordinates) * u_SubTextureSize) / u_TextureSize;
}