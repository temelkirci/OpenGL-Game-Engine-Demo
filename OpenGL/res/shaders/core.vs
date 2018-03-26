#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoordinate;

out vec3 outColor;
out vec2 texCoord;

void main()
{
	gl_Position = vec4(position, 1.0);
	outColor = color;

	texCoord = vec2(textureCoordinate.x, 1.0 - textureCoordinate.y);
}