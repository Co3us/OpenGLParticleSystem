#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>
class Input
{
public:
	Input(GLFWwindow* _window);
	void processInput(Camera &camera);
	GLFWwindow* window;
};

