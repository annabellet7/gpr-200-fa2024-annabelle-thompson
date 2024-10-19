#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <ew/external/stb_image.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader/Shader.h"
#include "Texture/Texture.h"
#include "Camera/Camera.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX = 400, lastY = 300;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720; 

void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
	printf("Initializing...\n");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	//Initialization goes here!
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Shader characterShader("assets/shaderAssets/vShader.vert", "assets/shaderAssets/fShader.frag");
	Shader bgShader("assets/shaderAssets/bgvShader.vert", "assets/shaderAssets/bgfShader.frag");

	//-----------------------------------------------------------------------------------------------

	float verts[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = 
	{  
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glm::vec3 posRand[20];
	for (int i = 0; i < 20; i++)
	{
		posRand[i].x = ew::RandomRange(-5.0, 5.0f);
		posRand[i].y = ew::RandomRange(-5.0f, 5.0f);
		posRand[i].z = ew::RandomRange(-10.0f, -5.0f);
	}

	float rotationAngleRand[20];
	for (int i = 0; i < 20; i++)
	{
		rotationAngleRand[i] = ew::RandomRange(-179, 179);
	}

	glm::vec3 rotationAxisRand[20];
	for (int i = 0; i < 20; i++)
	{
		rotationAxisRand[i].x = ew::RandomRange(-10.0, 10.0f);
		rotationAxisRand[i].y = ew::RandomRange(-10.0f, 10.0f);
		rotationAxisRand[i].z = ew::RandomRange(-10.0f, 0.0f);
	}

	glm::vec3 scaleRand[20];
	for (int i = 0; i < 20; i++)
	{
		scaleRand[i].x = ew::RandomRange(1.0, 20.0f);
		scaleRand[i].y = scaleRand[i].x;
		scaleRand[i].z = scaleRand[i].x;
	}



	unsigned int VBO; //vertex buffer object: can stores vertices on GPU memory, can send large amounts of data at a time
	unsigned int VAO; //vertex array object: has a pointer to a VBO, EBO, and attributes (mesh)
	unsigned int EBO; //element buffer object: stores indinces

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); //sets mesh that is being worked on, do this before binding VBO
	
	//copy verts into buffer
	glGenBuffers(1, &VBO); //generates unique id for buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //sets buffer that is currently being worked on
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); //copies previously assigned data into buffer memory

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set attib pointers
	//pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//uv
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Texture2D webTexture("assets/Textures/web.jpg", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_RGB);
	Texture2D boxTexture("assets/Textures/container.jpg", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT, GL_RGB);

	//set active shader and set textures to units
	bgShader.Shader::use();
	glUniform1i(glGetUniformLocation(bgShader.getProgram(), "texture2"), 1);
	glUniform1i(glGetUniformLocation(bgShader.getProgram(), "texture3"), 2);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		//update time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		//input
		processInput(window);
		glfwSetCursorPosCallback(window, mouseCallback);
		glfwSetScrollCallback(window, scrollCallback);

		//Clear framebuffer
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

		//bind textures
		webTexture.Texture2D::bind(1);
		boxTexture.Texture2D::bind(2);

		//use shader
		bgShader.Shader::use();;

		//update uniform
		//time
		float time = glfwGetTime();
		int timeLoc = glGetUniformLocation(bgShader.mId, "uTime");
		glUniform1f(timeLoc, time);

		//camera view
		glm::mat4 projection = glm::perspective(glm::radians(cam.mZoom), 800.0f / 600.0f, 0.1f, 1000.0f);
		bgShader.setMat4("projection", projection);

		glm::mat4 view = cam.getViewMatrix();
		bgShader.setMat4("view", view);
		
		//draw
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 20; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::scale(model, scaleRand[i]);
			model = glm::translate(model, posRand[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(rotationAngleRand[i]), rotationAxisRand[i]);
			bgShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();

	printf("Shutting down...");
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam.keyboardInput(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam.keyboardInput(BACKWARD, deltaTime); 
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam.keyboardInput(LEFT, deltaTime); 
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam.keyboardInput(RIGHT, deltaTime); 
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	
	float xOffset = xpos - lastX;
	float yOffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	cam.mouseMoveInput(xOffset, yOffset);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	cam.mouseWheelInput(yOffset);
}
