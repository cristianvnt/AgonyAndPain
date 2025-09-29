#version 330 core
layout (location = 0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform vec4 someColor;
uniform sampler2D u_Texture;
uniform sampler2D u_Texture2;

void main()
{
	vec4 texColor = mix(texture(u_Texture, v_TexCoord), texture(u_Texture2, v_TexCoord), 0.3) * someColor;
	FragColor = texColor;
}