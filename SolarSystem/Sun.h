#pragma once
#include "Edge.h"
#include "Point.h"
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::mat4
#include <time.h>
#include "Mesh.h"

using namespace std;
class Sun
{
public:
	unsigned int VBO, VAO;
	glm::vec3 color;
	size_t vertCount;
	float angle=0;
	float step = 0;
	float scale = 1;
	glm::mat4 mModel = glm::mat4(1);

	Sun(float s, glm::vec3 color);
	~Sun();

	glm::mat4 getMModel();
private:
	void GetIcosahedronVertices(float s, glm::vec3 color, vector<float>* v);
	void Icosahedron(Mesh &mesh);
};

