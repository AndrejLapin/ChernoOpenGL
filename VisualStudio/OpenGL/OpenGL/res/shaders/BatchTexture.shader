#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in float texIndex;

out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP;
uniform vec2 u_aspect;

void main()
{
   gl_Position = vec4(position.x, position.y, position.z, position.w) * u_MVP;
   v_TexCoord = texCoord;// / u_aspect;
   v_TexIndex = texIndex;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

void main()
{
    int index = int(v_TexIndex);

    color = vec4(1.0, 1.0, 1.0, 1.0);// texture(u_Textures[index], v_TexCoord);
};