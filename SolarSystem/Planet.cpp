#include "Planet.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>


Planet::Planet(glm::vec3 color) :Body(color)
{
	angle = 0;
	angle2 = 0;
}

Planet::~Planet()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

Planet::Planet(const Planet & planet):Body(planet.color)
{
	//body
	name = planet.name;
	color = planet.color;
	step = planet.step;
	scale = planet.scale;
	//planet
	angle2 = planet.angle2;
	step2 = planet.step2;
	radius = planet.radius;
}

glm::mat4 Planet::getMModel()
{
	angle = step * float(glfwGetTime());
	angle2 = step2 * float(glfwGetTime());
	return glm::transpose( glm::mat4(
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, scale, 0,
		0, 0, 0, 1) *
			glm::mat4(
			cos(angle), 0, sin(angle), 0,
			0, 1, 0, 0,
			-sin(angle), 0, cos(angle), radius,
			0, 0, 0, 1) * 
					glm::mat4(
					cos(angle2), 0, sin(angle2), 0,
					0, 1, 0, 0,
					-sin(angle2), 0, cos(angle2), 0,
					0, 0, 0, 1));
}

glm::vec3 Planet::getCenterPosition()
{
	angle2 = step2 * glfwGetTime();
	glm::vec4 a = glm::vec4(0);
	a.z= radius;
	a.w = 1.0f;
	glm::mat4 b = glm::mat4(
		cos(angle2), 0, sin(angle2), 0,
		0, 1, 0, 0,
		-sin(angle2), 0, cos(angle2), 0,
		0, 0, 0, 1);
	return glm::vec3(a*b);
}

