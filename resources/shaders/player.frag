#version 330 core
layout (location = 0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform vec4 someColor;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord) * someColor;
	FragColor = texColor;
}