#version 330 core

in vec2 vTextureCoordinates;
in vec4 vColour;

uniform sampler2D uTexture;

out vec4 oColour;

void main()
{
    oColour = texture2D(uTexture, vTextureCoordinates) * vColour;
}