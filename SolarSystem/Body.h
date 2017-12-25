#pragma once
#include "Edge.h"
#include "Point.h"
#include <vector>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec3.hpp> // glm::mat4
#include <time.h>
#include "Mesh.h"

using namespace std;
class Body
{
public:
	glm::mat4 mModel = glm::mat4(1);
	vector<float> vertices;

	unsigned int VBO, VAO;
	glm::vec3 color;
	size_t vertCount;
	float step = 0;
	float scale = 1;

	Body(float s, glm::vec3 color);
	~Body();

	glm::mat4 virtual getMModel() { return mModel; }
	void SetColor();

protected:
	float angle=0;
private:
	void UpdateBuffers();

	void GetIcosahedronVertices(float s, glm::vec3 color, vector<float>* v);
	void Icosahedron(Mesh &mesh);
	
	//TODO delete
	vector<float> GetCubeVertices(float s, glm::vec3 color);
};

