#include "Body.h"
#include <glad\glad.h>


Body::Body(float s)
{

	float vertices[] = {
		// positions         // colors
		-1.0*s, -1.0*s,  1.0*s,  1.0, 0.0, 0.5,
		 1.0*s, -1.0*s,  1.0*s,  0.0, 1.0, 0.8,
		 1.0*s,  1.0*s,  1.0*s,  0.0, 0.0, 0.9,
		-1.0*s,  1.0*s,  1.0*s,  0.0, 0.0, 1.0,
		-1.0*s, -1.0*s, -1.0*s,  1.0, 0.0, 0.0,
		 1.0*s, -1.0*s, -1.0*s,  0.9, 1.0, 0.0,
		 1.0*s,  1.0*s, -1.0*s,  0.7, 0.0, 1.0,
		-1.0*s,  1.0*s, -1.0*s,  0.5 , 0.0, 0.0,
	};
	unsigned int indices[] = {  // note that we start from 0!
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

Body::~Body()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

glm::mat4 Body::getMModel()
{
	//mModel = glm::mat4(scale);
	mModel = glm::mat4(
		cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, radius,
		0, 0, 1, 0,
		0, 0, 0, 1);
	mModel = mModel * glm::mat4(
		cos(angle2), -sin(angle2), 0, 0,
		sin(angle2), cos(angle2), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	/*mModel = glm::mat4(
		1, 0, 0, 0,
		0, cos(angle), -sin(angle), 0,
		0, sin(angle), cos(angle), 0,
		0, 0, 0, 1);*/
	//mModel = glm::mat4(1);
	mModel = glm::transpose(mModel);
	angle += step;
	angle2 += step2;
	return mModel;
}
