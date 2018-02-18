#pragma once
#include "Body.h"
class Planet :
	public Body
{
public:
	float angle2; 
	float step2;
	float radius;

	Planet(glm::vec3 color);
	~Planet();
	Planet(const Planet &planet);

	glm::mat4 getMModel() override;
	glm::vec3 getCenterPosition() override;
};

