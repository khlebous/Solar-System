#pragma once
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> 
#include <list>

#include "Body.h"
#include "Sun.h"
#include "shader_m.h"

class GraphicsLibrary
{
public:
	int* WINDOW_WIDTH;
	int* WINDOW_HEIGHT;

	glm::vec3* cameraPosition;
	glm::vec3* cameraTarget;
	glm::vec3* upVector;

	GraphicsLibrary();
	~GraphicsLibrary();

	void Draw(Sun* sun, list<Body>* bodies, Shader ourShader, Shader sun_shader);
	void DrawBody(Body* body, Shader ourShader);

private:
	glm::mat4 mView;
	glm::mat4 mProj;

	void CountViewMatrix();
	void CountProjMatrix();
};

