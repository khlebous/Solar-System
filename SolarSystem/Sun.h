#pragma once
#include "Edge.h"
#include "Body.h"
#include "Point.h"
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::mat4
#include <time.h>
#include "Mesh.h"
#include "shader_m.h"

using namespace std;
class Sun :
	public Body
{
public:
	Sun(float s, glm::vec3 color);
	~Sun();

	Shader* shader;
	Shader sun_shader;
	
	glm::mat4 getMModel();
	void SetColor();
	void SetScale();
	void SetSunColorToShader();
	void Draw(glm::mat4 viewM, glm::mat4 projM);
};

