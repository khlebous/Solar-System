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
	
	int rb_shading = 0;
	int rb_lighting = 0;
	int rb_camera = 0;
	
	Shader *main_shader;
	Camera *camera;

	GUI();
	~GUI();
	
	void Draw();

private:
	//
	char *new_planet_name;
	glm::vec3 new_planet_color;
	float new_planet_step;
	float new_planet_step2;
	float new_planet_radius;
	float new_planet_scale;
	//
	bool show_test_window = true;
	bool show_main_window = true;
	bool show_add_new_planet_window = false;

	void SwitchLightingShadingShader();
};

