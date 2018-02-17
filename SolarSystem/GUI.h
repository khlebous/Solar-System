#pragma once
#include "SolarSystem.h"
#include "Sun.h"
#include "Camera.h"
#include "shader_m.h"
#include <glm/vec4.hpp> 
#include <list>

class GUI
{
public:

	int rb_shading = 0;
	int rb_lighting = 0;
	int rb_camera = 0;

	SolarSystem *ss;
	Shader *main_shader;
	Camera *camera;
	bool show_add_new_planet_window = false;

	GUI();
	~GUI();

	void Draw();

private:
	//
	char new_planet_name[12] = "Your Name0";
	int new_planet_nr = 1;
	glm::vec3 new_planet_color = { 1.0, 1.0, 0.0 };
	float new_planet_step;
	float new_planet_step2;
	float new_planet_radius;
	float new_planet_scale;
	//
	bool show_test_window = true;
	bool show_main_window = true;

	int planet_to_follow = 0;
	int camera_on_planet = 0;

	void SwitchLightingShadingShader();
};

