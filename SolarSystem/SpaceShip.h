#pragma once
#include <vector>
#include "shader_m.h"
#include "Camera.h"
#include <glm/vec3.hpp> 

using namespace std;

class SpaceShip
{
public:
	unsigned int VBO, VAO;
	Shader shader;
	Camera* camera;

	SpaceShip();
	~SpaceShip();

	glm::mat4 virtual getMModel();
	void Draw(glm::mat4 viewM, glm::mat4 projM);
private:
	vector<float> GetCubeVertices();
	
};

