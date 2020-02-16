#define STB_IMAGE_IMPLEMENTATION

#include "Global.h"
#include "OpenGLHelpers.h"
#include "ParticleSystem.h"
#include "OpenGLData.h"
#include "Camera.h";
#include "Input.h"

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float squareSize = 0.25f;
int NMAX = 0;

int main(int argc, char *argv[])
{

	NMAX = atoi(argv[1]);
	int numOfParticlesPerSecond = atoi(argv[2]);
	Global::setDrawType(argv[3]);

	Global::setParticleSize(squareSize);

	//// helper classes for OpenGl functions
	//// -----------------------------------
	OpenGLHelpers glHelpers;
	OpenGLData glData{};
	
	GLFWwindow* window = glHelpers.initWindow(SCR_WIDTH, SCR_HEIGHT);
	if (window == NULL)
		return -1;

	if (!glHelpers.initOpenGL())
		return -1;

	Camera camera{(int) SCR_WIDTH,(int)SCR_HEIGHT, window};

	////select shader sources based on drawtype
	//// --------------------------------------
	char* vert, *frag, *geom;
	glHelpers.selectShaders(vert, frag, geom);

	glData.shaderProgram = glHelpers.compileShaders(vert, frag, geom);
	glData.texture=glHelpers.loadTexture();

	glHelpers.setUpVertexData(glData);

	ParticleSystem ps(NMAX, numOfParticlesPerSecond);
	Input input{window};

	while (!glfwWindowShouldClose(window))
	{
		input.processInput(camera);
		ps.update();
		camera.updateCamera(glData);

		if (Global::drawtype == Basic) {
			glHelpers.basicDataPrep(glData, ps);
			int numOfSquares = ps.getCurrentDataSize() / 8;
			glHelpers.basicRender(glData, numOfSquares);
		}
		else if (Global::drawtype == Geometry) {
			glHelpers.geometryDataPrep(glData, ps);
			glHelpers.geometryRender(glData, ps.getCurrentDataSize());
		}
		else if (Global::drawtype == Instanced) {
			glHelpers.instancedDataPrep(glData, ps);
			glHelpers.instancedRender(glData, ps.getCurrentDataSize());
		}

		//// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		//// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

}





