#include "Sun.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <map>

Sun::Sun(float s, glm::vec3 color) :Body(s, color) 
{
	sun_shader = Shader("Shaders/sun_shader.vs", "Shaders/sun_shader.fs");
	planets = list<Planet>();
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
	planet_shader->use();
	planet_shader->setVec3("lightColor", color);
	glUseProgram(0);
}

void Sun::DrawSunWithPlanets(glm::mat4 viewM, glm::mat4 projM, glm::vec3 camPos)
{
	sun_shader.use();
	sun_shader.setMat4("view", viewM);
	sun_shader.setMat4("proj", projM);
	sun_shader.setMat4("model", getMModel());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);

	planet_shader->use();
	planet_shader->setMat4("view", viewM);
	planet_shader->setMat4("proj", projM);
	planet_shader->setVec3("viewPos",camPos);
	for (Planet &b : planets)
	{
		planet_shader->setMat4("model", b.getMModel());
		glBindVertexArray(b.VAO);
		glDrawArrays(GL_TRIANGLES, 0, b.vertCount);
		//glDrawElements(GL_TRIANGLES, b.vertCount/2, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 3 * 1, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
	glUseProgram(0);

	glUseProgram(0);
	glBindVertexArray(0);
}
