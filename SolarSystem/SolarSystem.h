#pragma once
#include "Sun.h"
#include "Planet.h"
#include "shader_m.h"
class SolarSystem
{
public:
	Sun *sun;
	vector<Planet> planets;
	Shader* planet_shader;

	SolarSystem();
	~SolarSystem();

	void Draw(glm::mat4 viewM, glm::mat4 projM, glm::vec3 camPos, glm::vec3 camFront);
	void SetSunColorToShader();
	void AddNewPlanet(const char* planetName, glm::vec3 color, float velocity1, float velocity2, float radius, float scale);
};

