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
#include <iostream>
#include <vector>
#include <glm/vec4.hpp> 


#include "shader.h"
#include "GUI.h"
#include "GraphicsLibrary.h"
#include "SolarSystem.h"
#include "Sun.h"
#include "Planet.h"
#include "Camera.h"
#include "Skybox.h"
#include "SpaceShip.h"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void error_callback(int error, const char* description);
int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Camera camera = Camera();
GUI gui = GUI();

float lastX = WINDOW_WIDTH / 2.0;
float lastY = WINDOW_HEIGHT / 2.0;
bool firstMouse = true;
bool leftButtonPressed = false;

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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

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

	Shader planet_shader("Shaders/phong_shading_phong_lighting.vs", "Shaders/phong_shading_phong_lighting.fs");

	ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.2f, 1.0f);
	glm::vec3 color = { 1.0, 0.0, 0.0 };

	Sun sun = Sun({ 1.0, 1.0, 0.7 });
	sun.name = "Sun";
	sun.scale = 2.0;
	planet_shader.use();
	planet_shader.setVec3("lightColor", color);

	glUseProgram(0);
	sun.step = 0.1f;

	//Planet p1 = Planet(0.2, { 1.0, 0.0, 0.0 });
	//p1.step = 0.0f;
	//p1.step2 = 0.0f;
	//p1.radius = 2.0f;
	//p1.name = "Mars";
	//Planet p2 = Planet(0.4, { 0.0, 1.0, 0.5 });
	//p2.step = 0.5f;
	//p2.step2 = 0.5f;
	//p2.radius = 3.0f;
	//p2.name = "Earth";
	//Planet p3 = Planet(0.3, { 0.0, 0.0, 1.0 });
	//p3.step = 0.1f;
	//p3.step2 = 0.4f;
	//p3.radius = 2.5f;
	//p3.name = "Cos";

	// SOLAR SYSYEM
	SolarSystem ss = SolarSystem();
	ss.sun = &sun;
	ss.AddNewPlanet("mercury", { 0.8, 0.4, 0.2 }, 0.3f, 0.8324f, 4.0f, 0.15f);
	ss.AddNewPlanet("venus", { 1.0, 0.7, 0.2 }, 0.4f, 0.7234f, 5.0f, 0.2f);
	ss.AddNewPlanet("earth", { 0.4, 0.9, 0.5 }, 0.3f, 0.5234f, 6.0f, 0.3f);
	ss.AddNewPlanet("mars", { 1.0, 0.0, 0.0 }, 0.2f, 0.434f, 7.0f, 0.3f);
	ss.AddNewPlanet("jowisz", { 0.2, 0.5, 0.8 }, 0.6f, 0.24234f, 8.0f, 0.7f);
	/*ss.planets.push_back(p1);
	ss.planets.push_back(p2);
	ss.planets.push_back(p3);*/
	ss.planet_shader = &planet_shader;
	ss.SetSunColorToShader();
	// CAMERA
	camera.WINDOW_WIDTH = &WINDOW_WIDTH;
	camera.WINDOW_HEIGHT = &WINDOW_HEIGHT;
	camera.planet = (&ss.planets[0]);
	camera.updateCameraVectors();

	// GUI
	gui.ss = &ss;
	gui.main_shader = &planet_shader;
	gui.camera = &camera;

	// GL
	GraphicsLibrary gl = GraphicsLibrary();
	gl.WINDOW_WIDTH = &WINDOW_WIDTH;
	gl.WINDOW_HEIGHT = &WINDOW_HEIGHT;
	gl.camera = &camera;
	gl.ss = &ss;
	// SKYBOX
	//Skybox skybox = Skybox();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	// SPACESHIP
	SpaceShip spaceShip = SpaceShip();
	spaceShip.camera = &camera;

	glfwSetScrollCallback(window, scroll_callback);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

		// 
		//skybox.Draw(camera.GetViewMatrix(), camera.GetProjMatrix());
		//spaceShip.Draw(camera.GetViewMatrix(), camera.GetProjMatrix());
		gl.Draw();
		//

		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		gui.Draw();

		// 
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
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
	if (gui.show_add_new_planet_window)
		return;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (state == GLFW_RELEASE)
		return;
	camera.ProcessMouseMovement(xoffset, yoffset);
}
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
