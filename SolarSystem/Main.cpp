// ImGui - standalone example application for GLFW + OpenGL2, using legacy fixed pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the opengl3_example/ folder**
// See imgui_impl_glfw.cpp for details.

#include <glad\glad.h>
#include <GL/gl.h>
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
#include "shader_m.h"
#include <glm/vec4.hpp> 

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void error_callback(int error, const char* description);

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;

glm::vec3 cameraPosition = { 3, 0.2, 0.7 };
glm::vec3 cameraTarget = { 0, 0, 0 };
glm::vec3 upVector = { 0, 0, 0.5 };

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

int main(int, char**)
{
	// Setup window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
	//glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1); // Enable vsync

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// Setup ImGui binding
	ImGui_ImplGlfwGL2_Init(window, true);

	ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.2f, 1.0f);
	glm::vec3 color = { 1.0, 0.0, 0.0 };

	Body sun = Body(0.25, { 1.0, 1.0, 0.0 });
	sun.step = 0.005f;
	Body b1 = Body(0.15, color);
	b1.step = 0.005f;
	b1.step2 = 0.005f;
	b1.radius = 1.0f;

	list<Body> bodies = list<Body>();
	bodies.push_back(sun);
	bodies.push_back(b1);
	/*bodies.push_back(b2);
	bodies.push_back(b3);*/

	Shader ourShader("shader.vs", "shader.fs");
	//
	GraphicsLibrary gl = GraphicsLibrary();
	gl.WINDOW_WIDTH = &WINDOW_WIDTH;
	gl.WINDOW_HEIGHT = &WINDOW_HEIGHT;
	gl.cameraPosition = &cameraPosition;
	gl.cameraTarget = &cameraTarget;
	gl.upVector = &upVector;
	//
	//
	GUI gui = GUI();
	gui.cameraPosition = &cameraPosition;
	gui.cameraTarget = &cameraTarget;
	gui.upVector = &upVector;
	gui.color = &color;


	//

	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

		ourShader.use();
		//GL::Draw(&bodies, ourShader);
		gl.Draw(&bodies, ourShader);

		glUseProgram(0);

		gui.Draw();
		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
		glfwSwapBuffers(window);
		glfwPollEvents();
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

	float cameraSpeed = deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosition += cameraSpeed * (cameraTarget - cameraPosition);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosition -= cameraSpeed * (cameraTarget - cameraPosition);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPosition -= glm::normalize(glm::cross((cameraTarget - cameraPosition), upVector)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPosition += glm::normalize(glm::cross((cameraTarget - cameraPosition), upVector)) * cameraSpeed;
}

//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	if (fov >= 1.0f && fov <= 45.0f)
//		fov -= yoffset;
//	if (fov <= 1.0f)
//		fov = 1.0f;
//	if (fov >= 45.0f)
//		fov = 45.0f;
//}
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}