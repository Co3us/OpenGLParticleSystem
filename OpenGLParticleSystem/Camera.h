#pragma once
#define _USE_MATH_DEFINES
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include "OpenGLData.h"

class Camera
{
public:

	Camera() {};
	Camera(int scrWidth,int scrHeight, GLFWwindow* _window);

	void updateCamera(OpenGLData &glData);

	glm::vec3 getPosition();
	void setPosition(glm::vec3 _position);

	glm::vec3 getDirection();
	glm::vec3 getUpVector();
	glm::vec3 getRightVector();

	void setHorizotalAngle(float angle);
	float getHorizontalAngle();

	void setVerticalAngle(float angle);
	float getVerticalAngle();

	float getMoveSpeed();
	float getTurnSpeed();

private: 
	
	glm::vec3 position;     // position
	float horizontalAngle;	// horizontal angle : toward -Z
	float verticalAngle;   // vertical angle : 0, look at the horizon

	float moveSpeed;  //moving speed of the camera
	float turnSpeed;  //turning speed of the camera
	
	glm::vec3 direction; //direction camera looks at 
	glm::vec3 rightVec;  // camera vector for moving right
	glm::vec3 upVector;  //camera vector for moving up

	float screenWidth;
	float screenHeigth;
	GLFWwindow* window;
};

