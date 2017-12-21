#pragma once
#include "Edge.h"
#include "Point.h"
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec4.hpp> // glm::mat4

using namespace std;
class Body
{
public:
	unsigned int VBO, VAO, EBO;

	float angle=0;
	float angle2=0;
	float radius = 0;
	float step = 0;
	float step2 = 0;
	float scale = 1;
	glm::mat4 mModel = glm::mat4(1);

	vector<Edge> edges = vector<Edge>();
	vector<glm::vec4> points = vector<glm::vec4>();
	
	Body(float s);
	~Body();

	void Scale(float s);
	//void GenerateEdges();
	glm::mat4 getMModel();
};

