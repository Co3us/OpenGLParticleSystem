#include "ParticleSystem.h"


using namespace std;

ParticleSystem::ParticleSystem(int _NMAX, int _numOfParticlesPerSecond) {

	NMAX = _NMAX;
	numOfParticlesPerSecond = _numOfParticlesPerSecond;

	prevTime = glfwGetTime();
	fpsTime = glfwGetTime();

	partCounter = 0;
	nbFrames = 0;
	maxFilledIndex = 0;
	currentDataSize = 0;
	squareSize = 0.25;

	particlesArray = new Particle[NMAX];
	flags = new bool[NMAX];

	for (size_t i = 0; i < NMAX; i++)
		flags[i] = false;
}

ParticleSystem::~ParticleSystem() {

	delete(particlesArray);
	delete(flags);
}
void ParticleSystem::update() {

	double currentTime = glfwGetTime();
	double deltaTime = currentTime - prevTime;
	prevTime = currentTime;
	nbFrames++;

	partCounter += ceil(numOfParticlesPerSecond * deltaTime);
	initParticles(partCounter);

	if (currentTime - fpsTime >= 1.0) { 
		cout << "FPS: " << nbFrames << "\n";
		fpsTime += 1.0;
		nbFrames = 0;
		partCounter = 0;
	}

	for (size_t i = 0; i <= maxFilledIndex; i++)
	{
		if (flags[i] == true) {
			particlesArray[i].lifeSpan -= deltaTime;
			particlesArray[i].position = particlesArray[i].position + particlesArray[i].startVel * deltaTime;
			if (particlesArray[i].lifeSpan <= 0) {
				destroyParticle(i);
			}
		}
	}
}
void ParticleSystem::destroyParticle(int index) {

	flags[index] = false;
	if (index == maxFilledIndex) {
		for (int i = maxFilledIndex; i >= 0; i--)
		{
			if (flags[i] == true) {
				maxFilledIndex = i;
				break;
			}
		}
	}
}

void ParticleSystem::initParticles(int n) {

	for (size_t i = 0; i < n; i++)
	{
		Particle particle{};
		for (size_t j = 0; j < NMAX; j++)
		{
			if (flags[j] == false) {
				particlesArray[j] = particle;
				flags[j] = true;
				if (j >= maxFilledIndex) {
					maxFilledIndex = j;
				}
				break;
			}
		}
	}
}
vector<glm::vec3> ParticleSystem::getDataSquarePoints() {

	int squareDim = 1;
	std::vector<glm::vec3> points;
	currentDataSize = 0;
	for (size_t i = 0; i <= maxFilledIndex; i++)
	{
		if (flags[i] == true) {
			getSquareFromCenter(particlesArray[i].position);
			for (size_t i = 0; i < 4; i++) {
				points.push_back(squarePoints[i]);
				currentDataSize++;
				if (i == 0) {
					points.push_back(glm::vec3(1, 0, 1));
					currentDataSize++;
				}
				else if (i == 1) {
					points.push_back(glm::vec3(0, 0, 1));
					currentDataSize++;
				}
				else if (i == 2) {
					points.push_back(glm::vec3(0, 1, 1));
					currentDataSize++;
				}
				else if (i == 3) {
					points.push_back(glm::vec3(1, 1, 1));
					currentDataSize++;
				}
			}
		}
	}
	return points;
}
std::vector<glm::vec3>ParticleSystem::getDataCenterPoints() {

	int squareDim = 1;
	std::vector<glm::vec3> points;
	currentDataSize = 0;
	for (size_t i = 0; i <= maxFilledIndex; i++)
	{
		if (flags[i] == true) {
			points.push_back(particlesArray[i].position);
			currentDataSize++;
		}
	}
	return points;
}

void ParticleSystem::getSquareFromCenter(glm::vec3 center) {

	float dist = squareSize;
	//Point down-left
	squarePoints[0] = center + glm::vec3(dist, -dist, 0);
	//Point up-left
	squarePoints[1] = center + glm::vec3(-dist, -dist, 0);
	//Point down-right
	squarePoints[2] = center + glm::vec3(-dist, dist, 0);
	//Point up_right
	squarePoints[3] = center + glm::vec3(dist, dist, 0);

}

int ParticleSystem::getCurrentDataSize() {
	return currentDataSize;
}
