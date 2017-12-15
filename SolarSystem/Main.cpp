// ImGui - standalone example application for GLFW + OpenGL2, using legacy fixed pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the opengl3_example/ folder**
// See imgui_impl_glfw.cpp for details.

#include <imgui/imgui.h>
#include "imgui_impl_glfw.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "GUI.h"
#include <iostream>
#include "Edge.h"
#include "Point.h"
#include <vector>
#include "GraphicsLibrary.h"
#include "Body.h"
using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void error_callback(int error, const char* description);


int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;

int main(int, char**)
{
	// Setup window
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return 1;
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Solar System", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1); // Enable vsync

	// Setup ImGui binding
	ImGui_ImplGlfwGL2_Init(window, true);

	ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.2f, 1.0f);
	GUI gui = GUI();
	Body sun = Body();
	sun.step = 0.0005f;
	sun.Scale(5);
	Body b1 = Body();
	b1.step = 0.005f;
	b1.step2 = 0.005f;
	b1.radius = 15.0f;
	b1.Scale(1.5);
	Body b2 = Body();
	b2.step = 0.005f;
	b2.step2 = 0.009f;
	b2.radius = 7.0f;
	Body b3 = Body();
	b3.step = 0.005f;
	b3.step2 = 0.009f;
	b3.radius = 20.0f;
	b3.Scale(2);
	list<Body> bodies = list<Body>();
	bodies.push_back(sun);
	bodies.push_back(b1);
	bodies.push_back(b2);
	bodies.push_back(b3);
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		GL::Draw(&bodies);
		gui.Draw();
		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplGlfwGL2_Shutdown();
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
}
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}