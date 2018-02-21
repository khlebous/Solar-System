#include "Sun.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <map>

Sun::Sun(glm::vec3 color) :Body(color) 
{
	sun_shader = Shader("Shaders/sun_shader.vs", "Shaders/sun_shader.fs");
};

Sun::~Sun()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

glm::mat4 Sun::getMModel()
{
	angle = step * glfwGetTime();
	return glm::transpose( glm::mat4(
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, scale, 0,
		0, 0, 0, 1) *
			glm::mat4(
			cos(angle), 0, sin(angle), 0,
			0, 1, 0, 0,
			-sin(angle), 0, cos(angle), 0,
			0, 0, 0, 1));
}