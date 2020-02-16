#version 330 core

layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 aTexCoord;
uniform mat4 PVM;
out vec2 TexCoords;

void main()
{
	gl_Position = PVM*vec4(aPos.x, aPos.y, aPos.z, 1.0);
	TexCoords = vec2(aTexCoord.x, aTexCoord.y);
}