#pragma once
#include "Body.h"
class Planet :
	public Body
{
public:
	float angle2; 
	float step2;
	float radius;

	Planet(float s, glm::vec3 color);
	~Planet();

	glm::mat4 getMModel() override;
};

