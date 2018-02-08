#include "SpaceShip.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>

SpaceShip::SpaceShip()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	vector<float> vertices = GetCubeVertices();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader = Shader("Shaders/space_ship_shader.vs", "Shaders/space_ship_shader.fs");

}


SpaceShip::~SpaceShip()
{
}

glm::mat4 SpaceShip::getMModel()
{
	//return glm::mat4(3.0, 0.0, 0.0, 0.0f,
	//				0.0, 1.0, 0.0, 0.0f,
	//				0.0, 0.0, 1.0, 0.0f,
	//				5.0, 5.0, 0.0, 1.0);
	/*return glm::mat4(1.0, 0.0, 0.0,camera->Front.x,
		0.0, 1.0, 0.0, camera->Front.y,
		0.0, 0.0, 1.0, camera->Front.z,
		0.0, 0.0, 0.0, 1.0);*/
	/*return glm::transpose(glm::mat4(0.1, 0.0, 0.0, camera->Position.x+camera->Front.x,
		0.0, 0.1, 0.0, camera->Position.y + camera->Front.y-0.2,
		0.0, 0.0, 0.1, camera->Position.z + camera->Front.z-0.5,
		0.0, 0.0, 0.0, 1.0 ));*/

	return glm::transpose( glm::mat4(0.7, 0.0, 0.0, camera->Position.x,
					0.0, 0.01, 0.0, camera->Position.y-0.1,
					0.0, 0.0, 0.7, camera->Position.z,
					0.0, 0.0, 0.0, 1.0));
}

void SpaceShip::Draw(glm::mat4 viewM, glm::mat4 projM)
{
	shader.use();
	shader.setMat4("view", viewM);
	shader.setMat4("projection", projM);
	shader.setMat4("model", getMModel());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindVertexArray(0);
	
	glUseProgram(0);
	glBindVertexArray(0);
}


vector<float> SpaceShip::GetCubeVertices()
{
	return {
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
}