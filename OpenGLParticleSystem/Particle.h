#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <stdlib.h>   
#include <time.h>  

class Particle {
public:
	Particle();

	glm::vec3 position;
	glm::vec3  startVel;
	double lifeSpan;
};

