#pragma once
#include "GUI.h"
#include "Sun.h"
#include "shader_m.h"
#include <glm/vec4.hpp> 

class GUI
{
public:
	glm::vec3* cameraPosition;
	glm::vec3* cameraTarget;
	glm::vec3* upVector;
	glm::vec3* color;

	Sun *sun;

	GUI();
	~GUI();
	
	void Draw();

private:
};

