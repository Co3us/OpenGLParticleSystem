#include "Input.h"
#include <iostream>
using namespace std;

Input::Input(GLFWwindow* _window)
{
	window = _window;
}

void Input::processInput(Camera &camera)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float moveSpeed = camera.getMoveSpeed();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)//FORWARD
		camera.setPosition(camera.getPosition() + camera.getDirection() * moveSpeed);
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)//BACK
		camera.setPosition(camera.getPosition() - camera.getDirection() * moveSpeed);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)//UP
		camera.setPosition(camera.getPosition() + camera.getUpVector() * moveSpeed);
	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)//DOWN
		camera.setPosition(camera.getPosition() - camera.getUpVector() * moveSpeed);
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//LEFT
		camera.setPosition(camera.getPosition() - camera.getRightVector() * moveSpeed);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//RIGHT
		camera.setPosition(camera.getPosition() + camera.getRightVector() * moveSpeed);

	 double xpos, ypos;
	 glfwGetCursorPos(window, &xpos, &ypos);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	if (glfwGetMouseButton(window,0)==GLFW_PRESS) {
		camera.setHorizotalAngle(camera.getHorizontalAngle() + camera.getTurnSpeed() * float(width / 2 - xpos));
		camera.setVerticalAngle(camera.getVerticalAngle()+camera.getTurnSpeed() * float(height / 2 - ypos));
	}

}




