#include "Camera.h"

Camera::Camera(int scrWidth, int scrHeight, GLFWwindow* _window )
{
	position = glm::vec3(0, 10, -20);

	horizontalAngle = 0.0f;
	verticalAngle = -0.5f;

	moveSpeed = 0.3f;
	turnSpeed = 0.0001f;

	screenWidth = (float)scrWidth;
	screenHeigth = (float)scrHeight;

	window = _window;

}
void Camera::updateCamera(OpenGLData &glData)
{
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	rightVec = glm::vec3(
		sin(horizontalAngle - M_PI / 2.0f),
		0,
		cos(horizontalAngle - M_PI / 2.0f)
	);

	upVector = glm::cross(rightVec, direction);

	// projection matrix
	glm::mat4 P = glm::perspective(glm::radians(60.0f), screenWidth / screenHeigth, 0.01f, 1000.0f);

	//view matrix
	glm::mat4 V = glm::mat4(1);  
	V = glm::lookAt(
		position,                 // Camera is here
		position + direction,     // and looks here : at the same position, plus "direction"
		upVector                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// model matrix
	glm::mat4 M = glm::mat4(1);  

	glData.PVM = P * V * M;
	int a = 0;
}

glm::vec3 Camera::getPosition()
{
	return position;
}

void Camera::setPosition(glm::vec3 _position)
{
	position = _position;
}

glm::vec3 Camera::getDirection()
{
	return direction;
}

glm::vec3 Camera::getUpVector()
{
	return upVector;
}

glm::vec3 Camera::getRightVector()
{
	return rightVec;
}

void Camera::setHorizotalAngle(float angle)
{
	horizontalAngle = angle;
}

float Camera::getHorizontalAngle()
{
	return horizontalAngle;
}

void Camera::setVerticalAngle(float angle)
{
	verticalAngle = angle;
}

float Camera::getVerticalAngle()
{
	return verticalAngle;
}

float Camera::getMoveSpeed()
{
	return moveSpeed;
}

float Camera::getTurnSpeed()
{
	return turnSpeed;
}




