/*
* Simple Triangle Render with OpenGL, GLFW, and GLAD.
* By Kyle McCahill
* Modified: 06.18.2023
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Filepaths for the shader source files. TODO: Need to look into exact paths in the future.
const char* vertexShaderSource = "resources/triangleVShader.vs";
const char* fragmentShaderSource = "resource/triangleFShader.vs";

//const c
int main()
{
	// GLFW: init and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// GLFW: create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Shader Testing", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create the GLFW Window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// GLAD: load all opengl functions and pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}
	
	// Init the shader program from source files.
	// for the filepath you have to specify based off of the root of the project. TODO: Look more into this filepath thing.
	Shader testShader(vertexShaderSource, "resources/triangleFShader.fs");

	// INIT: Vertices for the triangle.
	float vertices[] = {
		// position			color
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	
	// Vertex Array Object: Create an object to store vertex objects.
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Vertex Buffer: Creating a vertex buffer object, passing it to opengl.
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute in the vertex array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color in the verte array
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	// shader specific vars, declared before rendering
	float shaderOffset = 0.4;
	// Render loop: Main
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		testShader.use();
		testShader.setFloat("vertOffset", shaderOffset);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call IO events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	// delete objects once they are no longer being used.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
