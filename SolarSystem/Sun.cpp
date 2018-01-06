#include "Sun.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <map>

Sun::~Sun()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

glm::mat4 Sun::getMModel()
{
	angle = step * glfwGetTime();
	mModel = glm::mat4(
		cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1);
	mModel = glm::transpose(mModel);
	return mModel;
}

void Sun::SetColor()
{
	int aa = 100;
	float bb = float(aa) * 2.0;
	float cc = float(aa) / bb / 2.0;
	vector<float> colors = vector<float>(vertCount);
	for (size_t i = 6; i < vertices.size(); i += 9)
	{
		vertices[i] = color.x;
		vertices[i + 1] = color.y;
		//vertices[i ] = (rand() % aa) / bb - cc + color.x;
		//vertices[i + 1] = (rand() % aa) / bb - cc + color.y;
		if (rand() % 2 == 0)
			vertices[i + 2] = (rand() % aa) / bb - cc + color.z;
		else
			vertices[i + 2] = color.z;
	}
	SetSunColorToShader();
	Body::UpdateBuffers();
}
void Sun::SetScale()
{
	for (size_t i = 0; i < m.triangles.size(); i++)
	{
		int t1 = m.triangles[i];
		vertices[9*i] = m.vertices[t1].x*scale;
		vertices[9*i+1] = m.vertices[t1].y*scale;
		vertices[9*i+2] = m.vertices[t1].z*scale;
	}
	Body::UpdateBuffers();
}
void Sun::SetSunColorToShader()
{
	shader->use();
	shader->setVec3("lightColor", color);
	glUseProgram(0);
}