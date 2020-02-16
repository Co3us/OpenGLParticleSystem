#include"OpenGLHelpers.h"
using namespace std;

GLFWwindow* OpenGLHelpers::initWindow(int width, int height) {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window = glfwCreateWindow(width, height, "Particle System", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	return window;
}

bool OpenGLHelpers::initOpenGL() {
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Failed to initialize GLAD" << endl;
		return false;
	}
	return true;
}

char* slurp(const char *filename){
	
	ifstream in;
	in.open(filename, ifstream::in);
	stringstream sstr;
	sstr << in.rdbuf();
	in.close();
	string s = sstr.str();
	char* cstr = new char[s.size() + 1];
	copy(s.begin(), s.end(), cstr);
	cstr[s.size()] = '\0';
	return cstr;
}

void OpenGLHelpers::selectShaders(char* &vertexShaderSource, char* &fragmentShaderSource, char* &geometryShaderSource) {
	
	drawType drawtype = Global::drawtype;
	ofstream myfile;

	vertexShaderSource = NULL;
	fragmentShaderSource = NULL;
	geometryShaderSource = NULL;

	if (drawtype == Basic) {
		vertexShaderSource = slurp("Shaders/vertexShaderSourceBasic.vs");
		fragmentShaderSource = slurp("Shaders/fragmentShaderSourceBasic.frag");
	}
	else if (drawtype == Geometry) {
		vertexShaderSource = slurp("Shaders/vertexShaderSourceGeometry.vs");
		fragmentShaderSource = slurp("Shaders/fragmentShaderSourceGeometry.frag");
		geometryShaderSource = slurp("Shaders/geometryShaderSource.gs");
	}
	else if (drawtype == Instanced) {
		vertexShaderSource = slurp("Shaders/vertexShaderSourceInstanced.vs");
		fragmentShaderSource = slurp("Shaders/fragmentShaderSourceBasic.frag");
	}
}

int OpenGLHelpers::compileShaders(char* vertexShaderSource, char* fragmentShaderSource, char* geometryShaderSource) {
	
	// geometry shader
	int geometryShader = 0;
	if (geometryShaderSource != NULL) {
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
		compileShader(geometryShader);
	}

	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	compileShader(vertexShader);

	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	compileShader(fragmentShader);

	// link shaders
	int success;
	char infoLog[512];

	int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	if (geometryShaderSource != NULL) {
		glAttachShader(shaderProgram, geometryShader);
	}

	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	return shaderProgram;

	// delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}
void OpenGLHelpers::compileShader(int shader) {
	
	glCompileShader(shader);
	int success;
	char infoLog[512];

	// check for shader compile errors
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
int OpenGLHelpers::loadTexture() {

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load("Textures/rect.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	stbi_image_free(data);
	return texture;
}

void OpenGLHelpers::setUpVertexData(OpenGLData &glData) {

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	glGenVertexArrays(1, &glData.VAO);
	glGenBuffers(1, &glData.VBO);
	glGenBuffers(1, &glData.EBO);


	if (Global::drawtype==Instanced) {
		glGenVertexArrays(1, &glData.quadVAO);
		glGenBuffers(1, &glData.quadVBO);
		glBindVertexArray(glData.quadVAO);

		float particleSize = Global::particleSize;
		glGenBuffers(1, &glData.instanceVBO);

		float quadVertices[] = {
			// positions    
			-particleSize,  particleSize,   0.0f, 1.0f,    // top left
			 particleSize, -particleSize,   1.0f, 0.0f,   // bottom right
			-particleSize, -particleSize,   0.0f, 0.0f,   // bottom left

			-particleSize,  particleSize,   0.0f, 1.0f,    // top left
			 particleSize,  -particleSize,  1.0f, 0.0f,   // bottom right
			 particleSize,  particleSize,   1.0f, 1.0f,   // top right 
		};
		glBindBuffer(GL_ARRAY_BUFFER, glData.quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	}
}

void OpenGLHelpers::basicDataPrep(OpenGLData &glData, ParticleSystem &ps) {


	std::vector<glm::vec3>  points = ps.getDataSquarePoints();
	int currentDataSize = ps.getCurrentDataSize();

	glm::vec3 *data = points.data();

	int numOfSquares = (currentDataSize / 8);
	std::vector<int> indices;
	for (size_t i = 0; i < numOfSquares; i++)
	{
		indices.push_back(i * 4);
		indices.push_back(i * 4 + 1);
		indices.push_back(i * 4 + 3);
		indices.push_back(i * 4 + 1);
		indices.push_back(i * 4 + 2);
		indices.push_back(i * 4 + 3);
	}
	int *indicesData = indices.data();

	if (currentDataSize > 0) {
		glBindVertexArray(glData.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, glData.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*currentDataSize, data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfSquares * 6 * sizeof(int), indicesData, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(1);

	}

}
void OpenGLHelpers::geometryDataPrep(OpenGLData &glData, ParticleSystem &ps)
{
	std::vector<glm::vec3>  points = ps.getDataCenterPoints();
	glm::vec3 *data = points.data();
	int currentDataSize = ps.getCurrentDataSize();

	int numOfSquares = (currentDataSize / 8);

	if (currentDataSize > 0) {
		glBindVertexArray(glData.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, glData.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*currentDataSize, data, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(0);
	}

}

void OpenGLHelpers::instancedDataPrep(OpenGLData & glData, ParticleSystem & ps)
{
	std::vector<glm::vec3>  points = ps.getDataCenterPoints();
	glm::vec3 *data = points.data();
	int currentDataSize = ps.getCurrentDataSize();

	if (currentDataSize > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, glData.instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * currentDataSize, data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, glData.instanceVBO); // this attribute comes from a different vertex buffer
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.
	}

}

void OpenGLHelpers::renderPrep(OpenGLData &glData, unsigned int VAO)
{
	glUniformMatrix4fv(glData.id_shader_PVM_uniform, 1, GL_FALSE, glm::value_ptr(glData.PVM));
	glUniform1f(glGetUniformLocation(glData.shaderProgram, "squareSize"), Global::particleSize);

	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glUseProgram(glData.shaderProgram);
	glBindTexture(GL_TEXTURE_2D, glData.texture);
	glBindVertexArray(VAO);
}

void OpenGLHelpers::basicRender(OpenGLData &glData, int numOfSquares) {

	renderPrep(glData,glData.VAO);
	glDrawElements(GL_TRIANGLES, numOfSquares * 6, GL_UNSIGNED_INT, 0);

}

void OpenGLHelpers::geometryRender(OpenGLData & glData, int currentDataSize)
{
	renderPrep(glData, glData.VAO);
	glDrawArrays(GL_POINTS, 0, currentDataSize);
}

void OpenGLHelpers::instancedRender(OpenGLData & glData, int currentDataSize)
{
	renderPrep(glData, glData.quadVAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, currentDataSize); 
	glBindVertexArray(0);
}
