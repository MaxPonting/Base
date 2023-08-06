#version 330 core

uniform vec4 u_Colour;

out vec4 o_Colour;

void main()
{
    o_Colour = u_Colour;
}