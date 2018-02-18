#include "Sun.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <map>

Sun::Sun(float s, glm::vec3 color) :Body(s, color) 
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
	mModel = glm::mat4(
		scale, 0, 0, 0,
		0, scale, 0, 0,
		0, 0, scale, 0,
		0, 0, 0, 1);
	mModel = mModel * glm::mat4(
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
	Body::UpdateBuffers();
}



