#include "Global.h"

drawType Global::drawtype=Basic;
float Global::particleSize;

void Global::setParticleSize(float _particleSize) {
	particleSize = _particleSize;
}
void Global::setDrawType(char* code) {
	if (*code == '0')
		drawtype = Basic;
	else if (*code == '1')
		drawtype = Geometry;
	else if (*code == '2')
		drawtype = Instanced;
}





