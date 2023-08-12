#version 430 core

layout(location = 0) in vec4 a_Position;

layout (std140, binding = 0) uniform b_ViewProjection
{
    uniform mat4 u_View;
    uniform mat4 u_Projection;
};

void main()
{   
    gl_Position = u_Projection * u_View * a_Position; 
}