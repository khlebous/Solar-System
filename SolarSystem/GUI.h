#pragma once
#include "Sun.h"
#include "Camera.h"
#include "shader_m.h"
#include <glm/vec4.hpp> 
#include <list>

class GUI
{
public:
	glm::vec3* cameraPosition;
	glm::vec3* cameraTarget;
	glm::vec3* upVector;
	glm::vec3* color;

	Sun *sun;
	list<Body> *bodies;
	
	int rb_shading = 0;
	int rb_lighting = 0;
	int rb_camera = 0;
	
	Shader *main_shader;
	Camera *camera;

	GUI();
	~GUI();
	
	void Draw();

private:
	void SwitchLightingShadingShader();
};

