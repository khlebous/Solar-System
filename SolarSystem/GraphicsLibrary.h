#pragma once
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> 
#include <list>

#include "Body.h"
#include "Planet.h"
#include "Sun.h"
#include "Camera.h"
#include "shader_m.h"

class GraphicsLibrary
{
public:
	int* WINDOW_WIDTH;
	int* WINDOW_HEIGHT;

	glm::vec3* cameraPosition;
	glm::vec3* cameraTarget;
	glm::vec3* upVector;

	Camera *camera;
	Sun* sun;
	Shader* main_shader;

	GraphicsLibrary();
	~GraphicsLibrary();

	void Draw(Sun* sun, list<Planet>* planets);

};

