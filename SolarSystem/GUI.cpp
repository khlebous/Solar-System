#include "GUI.h"
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
		ImGui::Text("Position of camera");
		ImGui::InputFloat("CamPos X", &((*cameraPosition).x), 0.1);
		ImGui::InputFloat("CamPos Y", &((*cameraPosition).y), 0.1);
		ImGui::InputFloat("CamPos Z", &((*cameraPosition).z), 0.1);

		ImGui::Text("Camera target");
		ImGui::InputFloat("CamTrg X", &((*cameraTarget).x), 0.1);
		ImGui::InputFloat("CamTrg Y", &((*cameraTarget).y), 0.1);
		ImGui::InputFloat("CamTrg Z", &((*cameraTarget).z), 0.1);

		ImGui::Text("Up vector");
		ImGui::InputFloat("UpVec X", &((*upVector).x), 0.01);
		ImGui::InputFloat("UpVec Y", &((*upVector).y), 0.01);
		ImGui::InputFloat("UpVec Z", &((*upVector).z), 0.01);

		ImGui::GetStateStorage()->SetInt(ImGui::GetID("Sun"), 1);
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
