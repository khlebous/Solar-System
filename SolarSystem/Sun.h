#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
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

	Shader sun_shader;
	
	glm::mat4 getMModel();
	void SetColor();
	void SetScale();
};

