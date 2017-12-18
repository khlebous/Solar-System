#include "Body.h"
#include <glad\glad.h>


Body::Body()
{
	points.push_back(glm::vec4(-0.5, -0.5, -0.5, 1.0));
	points.push_back(glm::vec4(0.5, -0.5, -0.5, 1.0));
	points.push_back(glm::vec4(-0.5, 0.5, -0.5, 1.0));
	points.push_back(glm::vec4(0.5, 0.5, -0.5, 1.0));
	points.push_back(glm::vec4(-0.5, -0.5, 0.5, 1.0));
	points.push_back(glm::vec4(0.5, -0.5, 0.5, 1.0));
	points.push_back(glm::vec4(-0.5, 0.5, 0.5, 1.0));
	points.push_back(glm::vec4(0.5, 0.5, 0.5, 1.0));
	GenerateEdges();
	angle = 0.0f;

	//float vertices[] = {
	//	// positions         // colors
	//	- 0.5, -0.5, 0.5,  1.0f, 0.0f, 0.0f,  // top right
	//	0.5, -0.5, 0.5,  0.0f, 1.0f, 0.0f,  // bottom right
	//	0.5, 0.5, 0.5,  0.0f, 0.0f, 1.0f  // top left
	//	-0.5, 0.5, 0.5,  1.0f, 1.0f, 1.0f,   // bottom left
	//	-0.5, -0.5, -0.5,  1.0f, 0.0f, 0.0f,  // top right
	//	0.5, -0.5, -0.5,  0.0f, 1.0f, 0.0f,  // bottom right
	//	0.5, 0.5, -0.5,  1.0f, 1.0f, 1.0f  // top left
	//	-0.5, 0.5, -0.5,  0.0f, 0.0f, 1.0f,   // bottom left
	//};
	float vertices[] = {
		// positions         // colors
		-0.5, -0.5,  0.5,   1.0, 0.0, 0.0,
		0.5, -0.5,  0.5,    0.0, 1.0, 0.0,
		0.5,  0.5,  0.5,    0.0, 0.0, 1.0,
		-0.5,  0.5,  0.5,    1.0, 1.0, 1.0,
		// back
		-0.5, -0.5, -0.5,    1.0, 0.0, 0.0,
		0.5, -0.5, -0.5,    0.0, 1.0, 0.0,
		0.5, 0.5, -0.5,      0.0, 0.0, 1.0,
		-0.5,  0.5, -0.5,    1.0, 1.0, 1.0,
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
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
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

void Body::Scale(float s)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i] *= s;
		points[i].w = 1;
	}
	GenerateEdges();
}

void Body::GenerateEdges()
{
	edges = vector<Edge>();
	Edge e1;
	e1.p1 = points[0];
	e1.p2 = points[1];
	edges.push_back(e1);
	Edge e2;
	e2.p1 = points[0];
	e2.p2 = points[2];
	edges.push_back(e2);
	Edge e3;
	e3.p1 = points[2];
	e3.p2 = points[3];
	edges.push_back(e3);
	Edge e4;
	e4.p1 = points[1];
	e4.p2 = points[3];
	edges.push_back(e4);
	Edge e5;
	e5.p1 = points[0];
	e5.p2 = points[4];
	edges.push_back(e5);
	Edge e6;
	e6.p1 = points[1];
	e6.p2 = points[5];
	edges.push_back(e6);
	Edge e7;
	e7.p1 = points[2];
	e7.p2 = points[6];
	edges.push_back(e7);
	Edge e8;
	e8.p1 = points[3];
	e8.p2 = points[7];
	edges.push_back(e8);
	Edge e9;
	e9.p1 = points[4];
	e9.p2 = points[5];
	edges.push_back(e9);
	Edge e10;
	e10.p1 = points[4];
	e10.p2 = points[6];
	edges.push_back(e10);
	Edge e11;
	e11.p1 = points[5];
	e11.p2 = points[7];
	edges.push_back(e11);
	Edge e12;
	e12.p1 = points[6];
	e12.p2 = points[7];
	edges.push_back(e12);
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
	angle += step;
	angle2 += step2;
	return mModel;
}
