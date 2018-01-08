#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <list>
#include <time.h>

#include "shader_m.h"
#include "Body.h"
#include "Mesh.h"
#include "Planet.h"


using namespace std;
class Sun :
	public Body
{
public:
	Sun(float s, glm::vec3 color);
	~Sun();

	list<Planet> planets;
	Shader* planet_shader;
	Shader sun_shader;
	
	glm::mat4 getMModel();
	void SetColor();
	void SetScale();
	void SetSunColorToShader();
	void DrawSunWithPlanets(glm::mat4 viewM, glm::mat4 projM, glm::vec3 camPos);
};

