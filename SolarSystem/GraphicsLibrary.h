#pragma once
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> 
#include <list>

#include "Body.h"
#include "shader_m.h"

class GraphicsLibrary
{
public:
	int* WINDOW_WIDTH;
	int* WINDOW_HEIGHT;

	float* cameraPosition;
	glm::vec3* cameraTarget;
	glm::vec3* upVector;

	GraphicsLibrary();
	~GraphicsLibrary();

	void Draw(list<Body>* bodies, Shader ourShader);
	void DrawBody(Body* body, Shader ourShader);

private:
	glm::mat4 mView;
	glm::mat4 mProj;

	void CountViewMatrix();
	void CountProjMatrix();
};

