#version 330 core

in vec2 v_TextureCoordinates;

uniform vec4 u_Colour;
uniform sampler2D u_Textures[4];

out vec4 o_Colour;

void main()
{
    o_Colour = texture2D(u_Textures[0], v_TextureCoordinates) * u_Colour;
}