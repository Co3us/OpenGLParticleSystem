#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Global.h"
#include "ParticleSystem.h"
#include "OpenGLData.h"

class OpenGLHelpers {
public:
	GLFWwindow* initWindow(int width, int height);
	bool initOpenGL();
	void selectShaders( char* &vertexShaderSource,  char* &fragmentShaderSource,  char* &geometryShaderSource);

	void compileShader(int shader);
	int compileShaders(char* vertexShaderSource,  char* fragmentShaderSource, char* geometryShaderSource);

	void setUpVertexData( OpenGLData &glData);
	int loadTexture();
		
	void basicDataPrep(OpenGLData &glData, ParticleSystem &ps);
	void geometryDataPrep(OpenGLData &glData, ParticleSystem &ps);
	void instancedDataPrep(OpenGLData &glData, ParticleSystem &ps);

	void basicRender(OpenGLData &glData, int numOfSquares);
	void geometryRender(OpenGLData &glData, int currentDataSize);
	void instancedRender(OpenGLData &glData, int currentDataSize);

	void renderPrep(OpenGLData &glData, unsigned int VAO);
};
