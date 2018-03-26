#version 430 core

in vec3 ourColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D ourTexture1;

void main()
{
	color = texture(ourTexture1, texCoord);
}