#version 330 core

layout(location = 0) in vec4 a_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform vec4 u_Color;

out vec4 v_Color;

void main()
{   
    gl_Position = u_Projection * u_View * u_Model * a_Position;
    v_Color = u_Color;
}