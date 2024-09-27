#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <ew/external/stb_image.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader/Shader.h"
#include "Texture/Texture.h"

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

	//Initialization goes here!
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Shader characterShader("assets/shaderAssets/vShader.vert", "assets/shaderAssets/fShader.frag");

	//-----------------------------------------------------------------------------------------------

	float verts[] =
	{
	//	X		Y		Z		R		G		B		A		U		V
		1.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,	1.0f,	1.0f,   // top right
		1.0f,	-1.0f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,	1.0f,	0.0f,   // bottom right
		-1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f,   // bottom left
		-1.0f,	1.0f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f,	0.0f,	1.0f    // top left 
	};

	unsigned int indices[] = 
	{  
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//primary color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Texture2D texture1("assets/Textures/pixil-frame-0.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT, GL_RGBA);
	//Texture2D texture2("assets/Textures/spider-web-seamless-pattern-2179584.jpg", GL_TEXTURE_MIN_FILTER, GL_NEAREST, GL_LINEAR, GL_REPEAT, GL_RGBA);

	characterShader.Shader::use();
	glUniform1i(glGetUniformLocation(characterShader.getProgram(), "texture1"), 0);
	//glUniform1i(glGetUniformLocation(characterShader.getProgram(), "texture2"), 1);


	//Render loop
	while (!glfwWindowShouldClose(window)) {
		//input
		glfwPollEvents();

		//Clear framebuffer
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//update uniform
		float time = glfwGetTime();
		int timeLoc = glGetUniformLocation(characterShader.mId, "uTime");
		glUniform1f(timeLoc, time);
		
		//draw
		texture1.Texture2D::bind();
		//texture2.Texture2D::bind(1);

		characterShader.Shader::use();
		glBindVertexArray(VAO);

		//Drawing happens here!
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();

	printf("Shutting down...");
}
