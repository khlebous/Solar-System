#include "Body.h"



Body::Body()
{
	points.push_back(glm::vec4(-0.5, -0.5, -0.5,1.0));
	points.push_back(glm::vec4(0.5, -0.5, -0.5,1.0));
	points.push_back(glm::vec4(-0.5, 0.5, -0.5,1.0));
	points.push_back(glm::vec4(0.5, 0.5, -0.5,1.0));
	points.push_back(glm::vec4(-0.5, -0.5, 0.5,1.0));
	points.push_back(glm::vec4(0.5, -0.5, 0.5,1.0));
	points.push_back(glm::vec4(-0.5, 0.5, 0.5,1.0));
	points.push_back(glm::vec4(0.5, 0.5, 0.5,1.0));
	GenerateEdges();
	angle = 0.0f;
}


Body::~Body()
{
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
	mModel =glm::mat4(
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
