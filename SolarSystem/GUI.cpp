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
		ImGui::Text("Position of camera");
		static glm::vec3 a = glm::vec3(1, 0.5, 1);
		ImGui::InputFloat("lalala", &a.x, 0.1);
		ImGui::InputFloat("lalala2", &a.y, 0.1);
		ImGui::InputFloat("CamPos X", &((*cameraPosition).x), 0.1);
		ImGui::InputFloat("CamPos Y", &((*cameraPosition).y), 0.1);
		ImGui::InputFloat("CamPos Z", &((*cameraPosition).z), 0.1);

		static float col1[3] = { 1.0f,0.0f,0.2f };
		static float col2[4] = { 0.4f,0.7f,0.0f,0.5f };
		ImGui::ColorEdit3("color 1", col1);

		/*ImGui::Text("Camera target");
		ImGui::InputFloat("CamTrg X", cameraTarget, 0.01);
		ImGui::InputFloat("CamTrg Y", cameraTarget + 1, 0.01);
		ImGui::InputFloat("CamTrg Z", cameraTarget + 2, 0.01);

		ImGui::Text("Up vector");
		ImGui::InputFloat("upVec X", upVector, 0.01);
		ImGui::InputFloat("upVec Y", upVector + 1, 0.01);
		ImGui::InputFloat("upVec Z", upVector + 2, 0.01);*/
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
