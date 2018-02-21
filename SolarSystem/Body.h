#pragma once
#include "Edge.h"
#include "Point.h"
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::mat4
#include <time.h>
#include "IMesh.h"

using namespace std;
class Body
{
public:
	string name;
	vector<float> vertices;
	unsigned int VBO, VAO;
	glm::vec3 color;
	size_t vertCount;
	float step = 0;
	float scale = 1;
	IMesh m;
	//
	glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8);
	glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
	float constant = 1.0f;
	float linear= 0.09f;
	float quadratic = 0.032f;
	//
	Body(glm::vec3 color);
	~Body();

	glm::mat4 virtual getMModel() { return glm::mat4(1); }
	glm::vec3 virtual getCenterPosition() { return glm::vec3(0); };

	void SetColor();

protected:
	float angle=0;
	void UpdateBuffers();


private:
	void GetIcosahedronVertices(glm::vec3 color, vector<float>* v);
	void Icosahedron(IMesh &IMesh);
	};

