#version 330 core

in vec2 vTextureCoordinates;
in vec4 vColour;

uniform sampler2D uTexture[1];

out vec4 oColour;

void main()
{
    oColour = texture2D(uTexture[0], vTextureCoordinates) * vColour;
}