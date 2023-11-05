#version 330 core

in vec2 vTextureCoordinates;

uniform sampler2D u_Texture;

out vec4 oColour;

void main()
{
    oColour = texture2D(u_Texture, vTextureCoordinates);
}