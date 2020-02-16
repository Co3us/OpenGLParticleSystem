#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 PVM;
uniform float squareSize;

out VS_OUT{
vec3 location;
vec4 dlPoint;
vec4 ulPoint;
vec4 drPoint;
vec4 urPoint;
}gs_in;

void main()
{
   gl_Position = PVM*vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gs_in.location=aPos;
   gs_in.dlPoint=PVM*(vec4(aPos.x, aPos.y, aPos.z, 1.0)+vec4(-squareSize,-squareSize,0,0));
   gs_in.ulPoint=PVM*(vec4(aPos.x, aPos.y, aPos.z, 1.0)+vec4(-squareSize,squareSize,0,0));
   gs_in.drPoint=PVM*(vec4(aPos.x, aPos.y, aPos.z, 1.0)+vec4(squareSize,-squareSize,0,0));
   gs_in.urPoint=PVM*(vec4(aPos.x, aPos.y, aPos.z, 1.0)+vec4(squareSize,squareSize,0,0));
}