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
	/*mModel = mModel * glm::mat4(
		cos(angle2), 0, sin(angle2), 0,
		0, 1, 0, 0,
		-sin(angle2), 0, cos(angle2), 0,
		0, 0, 0, 1);*/
	/*mModel = mModel * glm::mat4(
		1, 0, 0, 0,
		0, cos(angle2), -sin(angle2), 0,
		0, sin(angle2), cos(angle2), 0, 
		0, 0, 0, 1);*/
	mModel = glm::transpose(mModel);
	return mModel;
}

glm::vec3 Planet::getCenterPosition()
{
	//return glm::vec3(0.5);
	angle = step * glfwGetTime();
	angle2 = step2 * glfwGetTime();
	glm::vec4 a = glm::vec4(0);
	a.y= radius;
	a.w = 1.0f;/*
	glm::mat4 b = glm::mat4(
		cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, radius,
		0, 0, 1, 0,
		0, 0, 0, 1);*/
	glm::mat4 b = glm::mat4(
		cos(angle2), -sin(angle2), 0, 0,
	  sin(angle2), cos(angle2), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	glm::vec4 tmp = a * b;
	return glm::vec3(tmp);
}

