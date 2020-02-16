#version 330 core

layout (location = 0) in vec2 aPos;
layout(location = 1) in vec3 aTexCoord;
layout(location = 2) in vec3 aOffset;

uniform mat4 PVM;
out vec2 TexCoords;

void main()
{
	gl_Position = PVM*(vec4(aPos.x, aPos.y, 0, 1.0)+vec4(aOffset.xyz,0));
	TexCoords = vec2(aTexCoord.x, aTexCoord.y);
}