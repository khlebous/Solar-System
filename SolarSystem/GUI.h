#pragma once
#include "GUI.h"

#include <glm/vec4.hpp> 

class GUI
{
public:
	glm::vec3* cameraPosition;
	glm::vec3* cameraTarget;
	glm::vec3* upVector;

	GUI();
	~GUI();
	
	void Draw();

private:
};

