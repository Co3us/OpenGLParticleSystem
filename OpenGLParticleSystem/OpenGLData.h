#pragma once
#include <glm/glm.hpp>
class OpenGLData
{
public:
	OpenGLData();

	unsigned int id_shader_PVM_uniform;
	unsigned int id_shader_SquareSize_uniform;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int quadVAO;
	unsigned int quadVBO;
	unsigned int instanceVBO;

	int shaderProgram;
	int texture;

	glm::mat4 PVM;


};

