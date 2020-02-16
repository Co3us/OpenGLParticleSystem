#version 330 core

layout(points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT{
vec3 location;
vec4 dlPoint;
vec4 ulPoint;
vec4 drPoint;
vec4 urPoint;
}gs_in[];

out Outputs{
 vec2 TexCoords;
}GeoOut;


void main() {
	gl_Position = gs_in[0].dlPoint;
	GeoOut.TexCoords = vec2(0, 0);
	EmitVertex();

	gl_Position = gs_in[0].ulPoint;
	GeoOut.TexCoords = vec2(0, 1);
	EmitVertex();

	gl_Position = gs_in[0].drPoint;
	GeoOut.TexCoords = vec2(1, 0);
	EmitVertex();

	gl_Position = gs_in[0].urPoint;
	GeoOut.TexCoords = vec2(1, 1);
	EmitVertex();

	EndPrimitive();
}