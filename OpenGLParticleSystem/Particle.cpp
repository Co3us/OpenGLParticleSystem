#include "Particle.h"

Particle::Particle(){
	
	int rn = rand();
	double positionX = rand() / (double)RAND_MAX * 2 - 1;
	double positionY = rand() / (double)RAND_MAX * 2 - 1;
	double positionZ = rand() / (double)RAND_MAX * 2 - 1;
	double startVelX = ((rand() / (double)RAND_MAX) * 2 - 1) / 4;
	double startVelY = rand() / (double)RAND_MAX;
	double startVelZ = (rand() / (double)RAND_MAX * 2 - 1) / 5;

	position = glm::vec3(positionX, positionY, positionZ);
	startVel = 3*glm::vec3(startVelX, startVelY, startVelZ);
	lifeSpan = rand() / (double)RAND_MAX * 1 + 2;
}



