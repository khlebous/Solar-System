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

	planet_shader->use();
	planet_shader->setMat4("view", viewM);
	planet_shader->setMat4("proj", projM);
	planet_shader->setVec3("viewPos", camPos);
	// spot light
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
	// sun point light
	planet_shader->setVec3("pointLights[0].position", sun->getCenterPosition());
	planet_shader->setVec3("pointLights[0].color", sun->color);
	planet_shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	planet_shader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	planet_shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	planet_shader->setFloat("pointLights[0].constant", 1.0f);
	planet_shader->setFloat("pointLights[0].linear", 0.09);
	planet_shader->setFloat("pointLights[0].quadratic", 0.032);
	// planets point light
	for (size_t i = 1; i <= planets.size(); i++)
	{
		planet_shader->setVec3(("pointLights[" + to_string(i) + "].position").c_str(), planets[i-1].getCenterPosition());
		planet_shader->setVec3("pointLights[" + to_string(i) + "].color", planets[i-1].color);
		planet_shader->setVec3("pointLights[" + to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
		planet_shader->setVec3("pointLights[" + to_string(i) + "].diffuse", 0.8f, 0.8f, 0.8f);
		planet_shader->setVec3("pointLights[" + to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
		planet_shader->setFloat("pointLights[" + to_string(i) + "].constant", 1.0f);
		planet_shader->setFloat("pointLights[" + to_string(i) + "].linear", 0.09);
		planet_shader->setFloat("pointLights[" + to_string(i) + "].quadratic", 0.032);
	}

	for (Planet &p : planets)
	{
		planet_shader->setMat4("model", p.getMModel());
		glBindVertexArray(p.VAO);
		glDrawArrays(GL_TRIANGLES, 0, p.vertCount);
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

void SolarSystem::AddNewPlanet(const char * planetName, glm::vec3 color, float velocity1, float velocity2, float radius, float scale)
{
	Planet p1 = Planet(color);
	p1.scale = scale;
	p1.step = velocity1;
	p1.step2 = velocity2;
	p1.radius = radius;
	p1.name = planetName;
	planets.push_back(p1);
}

void SolarSystem::DeletePlanet(int nr)
{
	planets.erase(planets.begin() + nr);
}

