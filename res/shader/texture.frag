#version 330 core

in vec2 v_TextureCoordinates;

uniform vec4 u_Color;
uniform sampler2D u_Textures[4];

out vec4 o_Color;

void main()
{
    o_Color = texture2D(u_Textures[0], v_TextureCoordinates) * u_Color;
}