#define GLFW_INCLUDE_GLCOREARB
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "game.h"
#include "resource_manager.h"


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// The Width of the screen
const GLuint SCREEN_WIDTH = 1600;
// The height of the screen
const GLuint SCREEN_HEIGHT = 900;

Game gamebase(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GameBase", nullptr, nullptr);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	glfwSetKeyCallback(window, key_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
	gamebase.init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Start Game within Menu State
	gamebase.State = GAME_ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f;
		// Manage user input
		gamebase.processInput(deltaTime);

		// Update Game state
		gamebase.update(deltaTime, currentFrame);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*
		// now when we draw the triangle we first use the vertex and orange fragment shader from the first program
		glUseProgram(shaderProgramOrange);
		// draw the first triangle using the data from our first VAO
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output an orange triangle
		// then we draw the second triangle using the data from the second VAO
		// when we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output a yellow triangle*/

		gamebase.render();

		glfwSwapBuffers(window);
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		gamebase.Keys[key][0] = action;
		//gamebase.Keys[key][1] = action;
	}
	//gamebase.action = action;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
