#pragma once

#include <GLFW/glfw3.h>
#include"Particle.h"

#include<iostream>
#include <stdlib.h>   
#include <time.h>       
#include <vector>

class ParticleSystem {

public:
	ParticleSystem(int _NMAX, int _numOfParticlesPerSecond);
	~ParticleSystem();
	void initParticles(int n);
	void destroyParticle(int index);
	int getCurrentDataSize();
	std::vector<glm::vec3> getDataSquarePoints();
	void getSquareFromCenter(glm::vec3 center);
	void update();
	std::vector<glm::vec3> getDataCenterPoints();

private:
	int NMAX;
	int numOfParticlesPerSecond;
	int nbFrames;
	int currentDataSize;
	int partCounter;
	int maxFilledIndex;

	double prevTime;
	double fpsTime;

	float squareSize;
	bool* flags;

	Particle* particlesArray;
	glm::vec3 squarePoints[4];
	

	
};



