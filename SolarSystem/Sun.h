#pragma once
#include "Edge.h"
#include "Body.h"
#include "Point.h"
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::mat4
#include <time.h>
#include "Mesh.h"

using namespace std;
class Sun :
	public Body
{
public:

	Sun(float s, glm::vec3 color) :Body(s, color) {};
	~Sun();

	glm::mat4 getMModel();
};

