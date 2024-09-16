#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader/Shader.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720; 

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

	Shader ourShader("assets/shaderAssets/vShader.vert", "assets/shaderAssets/fShader.frag");

	//-----------------------------------------------------------------------------------------------

	float verts[] =
	{
	//	X		Y		Z		R		G		B		A
		-0.5f,	-0.5f,	0.0,	0.729f,	0.929f,	0.843f,			//bottom left
		 0.5f,	-0.5f,	0.0,	0.89f,	0.71f,	0.71f,			//bottom right
		 0.0f,	 0.5f,	0.0,	0.745f,	0.749f,	0.792f			//top
	};

	unsigned int VBO; //vertex buffer object: can stores vertices on GPU memory, can send large amounts of data at a time
	unsigned int VAO; 

	glGenBuffers(1, &VBO); //generates unique id for buffer
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	
	//copy verts into buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //sets buffer that is currently being worked on
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); //copies previously assigned data into buffer memory

	//set attib pointers
	//pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//Clear framebuffer
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//set program
		ourShader.Shader::use();
		
		//update uniform
		/*float time = glfwGetTime();
		float greenValue = (sin(time) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "uOurColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 0.0f);*/
		
		//draw
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}
