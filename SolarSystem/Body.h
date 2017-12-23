#pragma once
#include "Edge.h"
#include "Point.h"
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::mat4
#include <time.h>

using namespace std;
class Body
{
public:
	unsigned int VBO, VAO, EBO;
	glm::vec3 color;
	
	float angle=0;
	float angle2=0;
	float radius = 0;
	float step = 0;
	float step2 = 0;
	float scale = 1;
	glm::mat4 mModel = glm::mat4(1);

	Body(float s, glm::vec3 color);
	~Body();

	glm::mat4 getMModel();
private:
	float error(float a)
	{
		srand(time(NULL));
		a= (rand() % 100) / 100.0 - 0.5 +a;
		if (a < 0)
			a = 0;
		if (a > 1)
			a = 1;
		return a;
	};
};

