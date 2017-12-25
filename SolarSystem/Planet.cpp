#include "Planet.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>


Planet::Planet(float s, glm::vec3 color) :Body(s, color)
{
	angle = 0;
	angle2 = 0;
}


Planet::~Planet()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

glm::mat4 Planet::getMModel()
{
	angle = step * glfwGetTime();
	angle2 = step2 * glfwGetTime();
	mModel = glm::mat4(
		cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, radius,
		0, 0, 1, 0,
		0, 0, 0, 1);
	mModel = mModel * glm::mat4(
		cos(angle2), -sin(angle2), 0, 0,
		sin(angle2), cos(angle2), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	mModel = glm::transpose(mModel);
	return mModel;
}