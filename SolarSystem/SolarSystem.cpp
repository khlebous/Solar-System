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
	planet_shader->setVec3("pointLights[0].ambient", sun->ambient);
	planet_shader->setVec3("pointLights[0].diffuse", sun->diffuse);
	planet_shader->setVec3("pointLights[0].specular", sun->specular);
	planet_shader->setFloat("pointLights[0].constant", sun->constant);
	planet_shader->setFloat("pointLights[0].linear", sun->linear);
	planet_shader->setFloat("pointLights[0].quadratic", sun->quadratic);
	// planets point light
	planet_shader->setFloat("pointLightLength", planets.size() + 1);
	for (size_t i = 0; i < planets.size(); i++)
	{
		std::string s = "pointLights[" + to_string(i + 1);
		planet_shader->setVec3(s + "].position", planets[i].getCenterPosition());
		planet_shader->setVec3(s + "].color", planets[i].color);
		planet_shader->setVec3(s + "].ambient", planets[i].ambient);
		planet_shader->setVec3(s + "].diffuse", planets[i].diffuse);
		planet_shader->setVec3(s + "].specular", planets[i].specular);
		planet_shader->setFloat(s + "].constant", planets[i].constant);
		planet_shader->setFloat(s + "].linear", planets[i].linear);
		planet_shader->setFloat(s + "].quadratic", planets[i].quadratic);
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

