#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <list>
#include <time.h>

#include "shader.h"
#include "Body.h"
#include "IMesh.h"
#include "Planet.h"

using namespace std;
class Sun :
	public Body
{
public:
	Sun(glm::vec3 color);
	~Sun();

	Shader sun_shader;
	glm::mat4 getMModel();
};

