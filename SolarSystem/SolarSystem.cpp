#include "SolarSystem.h"



SolarSystem::SolarSystem()
{
}


SolarSystem::~SolarSystem()
{
}

void SolarSystem::Draw(glm::mat4 viewM, glm::mat4 projM, glm::vec3 camPos, glm::vec3 camFront)
{
	sun->sun_shader.use();
	sun->sun_shader.setMat4("view", viewM);
	sun->sun_shader.setMat4("proj", projM);
	sun->sun_shader.setMat4("model", sun->getMModel());
	glBindVertexArray(sun->VAO);
	glDrawArrays(GL_TRIANGLES, 0, sun->vertCount);
	//glBindVertexArray(0);

	planet_shader->use();
	planet_shader->setMat4("view", viewM);
	planet_shader->setMat4("proj", projM);
	planet_shader->setVec3("viewPos", camPos);
	planet_shader->setVec3("spotLight.position", camPos);
	planet_shader->setVec3("spotLight.direction", camFront);
	planet_shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	planet_shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	planet_shader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	planet_shader->setFloat("spotLight.constant", 1.0f);
	planet_shader->setFloat("spotLight.linear", 0.09);
	planet_shader->setFloat("spotLight.quadratic", 0.032);
	planet_shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(0.5f)));
	planet_shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(1.5f)));
	for (Planet *p : planets)
	{
		planet_shader->setMat4("model", p->getMModel());
		glBindVertexArray(p->VAO);
		glDrawArrays(GL_TRIANGLES, 0, p->vertCount);
		//glDrawElements(GL_TRIANGLES, b.vertCount/2, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 3 * 1, GL_UNSIGNED_INT, 0);
	}

	glUseProgram(0);
	glBindVertexArray(0);
}

void SolarSystem::SetSunColorToShader()
{
	planet_shader->use();
	planet_shader->setVec3("lightColor", sun->color);
	glUseProgram(0);
}