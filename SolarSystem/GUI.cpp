﻿#include "GUI.h"
#include <imgui\imgui.h>
#include <iostream>
#include <imgui\imgui_internal.h>
#include "imgui_impl_glfw.h"
#include <stdio.h>
#include <glm/vec3.hpp> 


GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::Draw()
{
	bool show_test_window = true;
	bool show_another_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui_ImplGlfwGL2_NewFrame();

	// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::SetWindowSize(ImVec2(300.0f, 600.0f));
		if (ImGui::RadioButton("Phong Shading", &rb_shading, 0))
			SwitchLightingShadingShader();
		if (ImGui::RadioButton("Gouraud Shading", &rb_shading, 1))
			SwitchLightingShadingShader();
		ImGui::Text("--------------------");
		if (ImGui::RadioButton("Phong Lighting Model", &rb_lighting, 0))
			SwitchLightingShadingShader();
		if (ImGui::RadioButton("Blinn-Phong Lighting Model", &rb_lighting, 1))
			SwitchLightingShadingShader();
		ImGui::Text("--------------------");
		if (ImGui::RadioButton("Camera on space ship", &rb_camera, 0))
		{
			camera->Mode = STATIC;
		}
		if (ImGui::RadioButton("Camera following planet", &rb_camera, 1))
		{
			camera->Mode = FOLLOWING_PLANET;
		}
		if (ImGui::RadioButton("Camera on a planet", &rb_camera, 2))
		{

		}
		ImGui::Text("--------------------");
		ImGui::Text("Position of camera");
		ImGui::InputFloat("CamPos X", &(((*camera).Position).x), 0.1);
		ImGui::InputFloat("CamPos Y", &(((*camera).Position).y), 0.1);
		ImGui::InputFloat("CamPos Z", &(((*camera).Position).z), 0.1);
		ImGui::Text("Camera Front");
		ImGui::InputFloat("CamFront X", &(((*camera).Front).x), 0.1);
		ImGui::InputFloat("CamFront Y", &(((*camera).Front).y), 0.1);
		ImGui::InputFloat("CamFront Z", &(((*camera).Front).z), 0.1);
		ImGui::Text("Up vector");
		ImGui::InputFloat("UpVec X", &(((*camera).Up).x), 0.01);
		ImGui::InputFloat("UpVec Y", &(((*camera).Up).y), 0.01);
		ImGui::InputFloat("UpVec Z", &(((*camera).Up).z), 0.01);
		ImGui::Text("Right vector");
		ImGui::InputFloat("RightVec X", &(((*camera).Right).x), 0.01);
		ImGui::InputFloat("RightVec Y", &(((*camera).Right).y), 0.01);
		ImGui::InputFloat("RightVec Z", &(((*camera).Right).z), 0.01);
		ImGui::Text("WorldUp vector");
		ImGui::InputFloat("WorldUpVec X", &(((*camera).WorldUp).x), 0.01);
		ImGui::InputFloat("WorldUpVec Y", &(((*camera).WorldUp).y), 0.01);
		ImGui::InputFloat("WorldUpVec Z", &(((*camera).WorldUp).z), 0.01);
		ImGui::Text("--------------------");
		ImGui::InputFloat("Yaw", &(*camera).Yaw, 0.01);
		ImGui::InputFloat("Pitch", &(*camera).Pitch, 0.01);
		ImGui::InputFloat("MovementSpeed", &(*camera).MovementSpeed, 0.01);
		ImGui::InputFloat("MouseSensitivity", &(*camera).MouseSensitivity, 0.01);
		ImGui::InputFloat("Zoom", &(*camera).Zoom, 0.01);
		ImGui::InputFloat("Nearest", &(*camera).n, 0.01);
		ImGui::InputFloat("Farest", &(*camera).f, 0.1);
		ImGui::Text("--------------------");

		//ImGui::GetStateStorage()->SetInt(ImGui::GetID("Sun"), 1);
		if (ImGui::CollapsingHeader("Sun"))
		{
			if (ImGui::ColorEdit3("color 1", &sun->color.x))
			{
				sun->SetColor();
			}
			ImGui::InputFloat("Rotation velocity", &(sun->step), 0.01);
			if (ImGui::InputFloat("Scale", &(sun->scale), 0.01))
			{
				sun->SetScale();
			}
		}
		/*for (size_t i = 0; i < bodies->size(); i++)
		{

		}*/
		ImGui::End();
	}

	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow().
	if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}


	//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
	ImGui::Render();

}

void GUI::SwitchLightingShadingShader()
{
	if (rb_shading == 0)
	{
		if (rb_lighting == 0)
			*main_shader = Shader("Shaders/phong_shading_phong_lighting.vs", "Shaders/phong_shading_phong_lighting.fs");
		else
			*main_shader = Shader("Shaders/phong_shading_blinn_phong_lighting.vs", "shaders/phong_shading_blinn_phong_lighting.fs");
	}
	else
	{
		if (rb_lighting == 0)
			*main_shader = Shader("Shaders/gouraud_shading_phong_lighting.vs", "Shaders/gouraud_shading_phong_lighting.fs");
		else
			*main_shader = Shader("Shaders/gouraud_shading_blinn_phong_lighting.vs", "Shaders/gouraud_shading_blinn_phong_lighting.fs");
	}
	sun->SetSunColorToShader();
}
