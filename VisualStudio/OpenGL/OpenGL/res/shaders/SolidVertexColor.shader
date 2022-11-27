#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;

out vec4 v_Color;

void main()
{
   v_Color = a_Color;
   gl_Position = a_Position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;

//uniform vec4 u_Color;

void main()
{
    o_Color = v_Color;
};