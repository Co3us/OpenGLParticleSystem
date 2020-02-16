#pragma once
enum drawType { Basic, Geometry, Instanced };

static class Global
{
public:
	static void setDrawType(char* code);
	static void setParticleSize(float _particleSize);
	static drawType drawtype;
	static float particleSize;
};

