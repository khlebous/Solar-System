#include "GUI.h"
#include <imgui\imgui.h>
#include <iostream>
#include <imgui\imgui_internal.h>
#include "imgui_impl_glfw.h"
#include <stdio.h>
#include <glm/vec3.hpp> 


GUI::GUI()
{
	new_planet_color = glm::vec3(1.0, 1.0, 0.0);
	new_planet_step = 0.5;
	new_planet_step2 = 1.0;
	new_planet_radius = 2.0;
	new_planet_scale = 0.5;
}

GUI::~GUI()
{
}

void GUI::Draw()
{

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui_ImplGlfwGL2_NewFrame();

	// 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
	if (show_main_window)
	{
		ImGui::Begin("Application configuration", &show_main_window);
		ImGui::SetWindowSize(ImVec2(300.0f, 600.0f));
		ImGui::Text("Application average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
		ImGui::Text("--------------------");
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
			camera_following_planet = false;
		}
		if (ImGui::RadioButton("Camera following planet", &rb_camera, 1))
		{
			camera->Mode = FOLLOWING_PLANET;
			camera_following_planet = true;
		}

		if (camera_following_planet)
			for (size_t i = 0; i < ss->planets.size(); i++)
			{
				ImGui::Text("	"); ImGui::SameLine();
				if (ImGui::RadioButton(ss->planets[i].name.c_str(), &planet_to_follow, i))
					camera->planet = &ss->planets[i];
			}
		if (ImGui::RadioButton("Camera on a planet", &rb_camera, 2))
		{

		}
		if (rb_camera == 2)
		{
			camera->Position = ss->planets[0].getCenterPosition();
			camera->Front = -camera->Position;
		}
		if (ImGui::CollapsingHeader("Camera Settings"))
		{
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
		}

		//ImGui::GetStateStorage()->SetInt(ImGui::GetID("Sun"), 1);
		if (ImGui::CollapsingHeader("Sun"))
		{
			if (ImGui::ColorEdit3("color 1", &ss->sun->color.x))
			{
				ss->sun->SetColor();
				ss->SetSunColorToShader();
			}
			ImGui::InputFloat("Rotation velocity", &(ss->sun->step), 0.01);
			if (ImGui::InputFloat("Scale", &(ss->sun->scale), 0.01))
			{
				ss->sun->SetScale();
			}
			int planetNr = 0;
			for (auto &p : ss->planets)
			{
				//if (ImGui::CollapsingHeader(p->name.c_str()))
				if (ImGui::TreeNode(("planet: " + p.name).c_str()))
				{
					if (ImGui::ColorEdit3(("color " + p.name).c_str(), &(p.color.x)))
					{
						p.SetColor();
					}
					ImGui::InputFloat(("rotation velocity" + p.name).c_str(), &(p.step), 0.01);
					ImGui::InputFloat(("rotation velocity2" + p.name).c_str(), &(p.step2), 0.01);
					ImGui::InputFloat(("radius" + p.name).c_str(), &(p.radius), 0.01);
					if (ImGui::InputFloat(("scale" + p.name).c_str(), &(p.scale), 0.01))
					{
						p.SetScale();
					}
					if (ImGui::Button("Delete planet"))
						ss->DeletePlanet(planetNr);
					ImGui::TreePop();
				}
				planetNr++;
			}
			if (ImGui::Button("Add new planet"))
			{
				srand(time(NULL));
				new_planet_color = { (rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0 };
				new_planet_step = (rand() % 100) / 100.0;
				new_planet_step2 = (rand() % 100) / 100.0;
				new_planet_radius = (rand() % 100) / 20.0+2.5;
				new_planet_scale = (rand() % 100) / 100.0 + 0.01;
				show_add_new_planet_window = true;
			}
		}
		ImGui::End();
	}

	if (show_add_new_planet_window)
	{
		ImGui::Begin("New planet", &show_add_new_planet_window);
		ImGui::InputText("Planet name", new_planet_name, IM_ARRAYSIZE(new_planet_name));
		ImGui::ColorEdit3("Planet color", &(new_planet_color.x));
		ImGui::InputFloat("Planet rotation velocity", &new_planet_step, 0.01);
		ImGui::InputFloat("Planet rotation velocity2", &new_planet_step2, 0.01);
		ImGui::InputFloat("Planet radius", &new_planet_radius, 0.01);
		ImGui::InputFloat("Planet scale", &new_planet_scale, 0.01);
		if (ImGui::Button("Add planet"))
		{
			ss->AddNewPlanet(new_planet_name, new_planet_color, new_planet_step, new_planet_step2, new_planet_radius, new_planet_scale);
			show_add_new_planet_window = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
			show_add_new_planet_window = false;
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
	ss->SetSunColorToShader();
}
