#pragma once
#include "GUI.h"

#include <glm/vec4.hpp> 

class GUI
{
public:
	float* cameraPosition;
	glm::vec3* cameraTarget;
	glm::vec3* upVector;

	GUI();
	~GUI();
	
	void Draw();

private:
};

