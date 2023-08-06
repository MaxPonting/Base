#version 330 core

in vec2 v_TextureCoordinates;

uniform vec4 u_Color;
uniform sampler2D u_Textures[4];
uniform vec2 u_LightPos;
uniform float u_LightRadius;

out vec4 o_Color;

void main()
{   
    vec4 color = texture2D(u_Textures[0], v_TextureCoordinates) * u_Color;

    vec4 light = vec4(0.0, 0.0, 0.0, 1.0);
    vec2 toLight = u_LightPos - gl_FragCoord.xy;
    float brightness = clamp(1.0 - (length(toLight) / u_LightRadius), 0.0, 1.0);
    light = light + brightness;

    o_Color = light * color + 0.2 * color;
}