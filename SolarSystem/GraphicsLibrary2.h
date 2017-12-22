#pragma once
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> 
#include <list>

#include "Body.h"
#include "shader_m.h"

class GraphicsLibrary2
{
public:
	glm::vec3 cameraPosition = glm::vec3(3, 3, 0.7);
	glm::vec3 cameraTarget = glm::vec3(0, 0.5, 0.5);
	glm::vec3 upVector = glm::vec3(1,1, 0.5);

	GraphicsLibrary2();
	~GraphicsLibrary2();

	void Draw(list<Body>* bodies, Shader ourShader);
	void DrawBody(Body* body, Shader ourShader);

private:
	glm::mat4 mView;
	glm::mat4 mProj;

	void CountViewMatrix();
	void CountProjMatrix();
};

