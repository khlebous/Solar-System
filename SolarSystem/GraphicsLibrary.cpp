#include "GraphicsLibrary.h"
#include <algorithm>  
#include <GLFW\glfw3.h>
#include <glm/gtc/constants.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::vec3
float angle = 0;
float r = 4;
float step = 0.005;

glm::vec3 cameraPosition = glm::vec3(50, 0, 20);
void GL::Draw(list<Body>* bodies)
{
	
	for (auto &b : *bodies)
	{
		DrawBody(&b);
	}
}

void GL::DrawBody(Body* body)
{
	glm::mat4 mModel;
	glm::mat4 mView;
	glm::mat4 mProj;

	//std::cout << r * sin(angle) << " " << r * cos(angle) << std::endl;
	//glm::vec3 cameraPosition = glm::vec3(r * sin(angle), r * cos(angle), 0.3);
	angle += step;
	glm::vec3 cameraTarget = glm::vec3(0, 0, 0);
	glm::vec3 upVector = glm::vec3(0, 0, 1);
	float upVecorNormal = glm::sqrt(upVector.x*upVector.x + upVector.y*upVector.y + upVector.z*upVector.z);
	glm::vec3 upVectorVersor = glm::vec3(upVector.x / upVecorNormal, upVector.y / upVecorNormal, upVector.z / upVecorNormal);

	glm::vec3 zAxis = cameraPosition - cameraTarget;
	float zAxisNormal = glm::sqrt(zAxis.x*zAxis.x + zAxis.y*zAxis.y + zAxis.z*zAxis.z);
	glm::vec3 zAxisVersor = glm::vec3(zAxis.x / zAxisNormal, zAxis.y / zAxisNormal, zAxis.z / zAxisNormal);

	glm::vec3 xAxis = glm::vec3(upVectorVersor.y * zAxisVersor.z - upVectorVersor.z*zAxisVersor.y,
		-upVectorVersor.x * zAxisVersor.z + upVectorVersor.z*zAxisVersor.x,
		upVectorVersor.x*zAxisVersor.y - upVectorVersor.y*zAxisVersor.x);
	float xAxisNormal = glm::sqrt(xAxis.x*xAxis.x + xAxis.y*xAxis.y + xAxis.z*xAxis.z);
	glm::vec3 xAxisVersor = glm::vec3(xAxis.x / xAxisNormal, xAxis.y / xAxisNormal, xAxis.z / xAxisNormal);

	glm::vec3 yAxis = glm::vec3(xAxisVersor.z * zAxisVersor.y - xAxisVersor.y*zAxisVersor.z,
		-xAxisVersor.z * zAxisVersor.x + xAxisVersor.x*zAxisVersor.z,
		xAxisVersor.y*zAxisVersor.x - xAxisVersor.x*zAxisVersor.y);

	mView = glm::mat4(xAxisVersor.x, yAxis.x, zAxisVersor.x, cameraPosition.x,
		xAxisVersor.y, yAxis.y, zAxisVersor.y, cameraPosition.y,
		xAxisVersor.z, yAxis.z, zAxisVersor.z, cameraPosition.z,
		0, 0, 0, 1);
	mView = glm::inverse(mView);


	int n = 1;
	int f = 100;
	float fov = 45.0;
	float a = float(600) / float(800);
	float e = 1 / tan(fov*glm::pi<float>() / 360.0);
	mProj = glm::mat4(e, 0, 0, 0,
		0, e / a, 0, 0,
		0, 0, -(f + n) / (f - n), -2.0*f*n*(f - n),
		0, 0, -1, 0);
	mModel = body->getMModel();
	mModel = glm::transpose(mModel);
	mView = glm::transpose(mView);
	mProj = glm::transpose(mProj);

	auto edges = body->edges;
	for (size_t i = 0; i < edges.size(); i++)
	{
		Edge e = edges[i];
		glm::vec4 eVec = glm::vec4(e.p1.x, e.p1.y, e.p1.z, 1);
		eVec = mProj * (mView*(mModel*eVec));
		eVec = glm::vec4(eVec.x / eVec.w, eVec.y / eVec.w, eVec.z / eVec.w, 1);

		eVec = (eVec + glm::vec4(1, 1, 1, 1)) / glm::vec4(2, 2, 2, 2);
		e.p1 = glm::vec4(eVec.x, eVec.y, eVec.z,1);

		eVec = glm::vec4(e.p2.x, e.p2.y, e.p2.z, e.p2.w);
		eVec = mProj * (mView*(mModel*eVec));
		eVec = glm::vec4(eVec.x / eVec.w, eVec.y / eVec.w, eVec.z / eVec.w, 1);

		eVec = (eVec + glm::vec4(1, 1, 1, 1)) / glm::vec4(2, 2, 2, 2);
		e.p2 = glm::vec4(eVec.x, eVec.y, eVec.z,1);
		edges[i] = e;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1280, 0.0, 720, 0.0, 1.0);

	glColor3f(1, 1, 1);
	glScalef(1, 1, 1);

	glBegin(GL_LINES);
	for (auto e : edges)
	{
		glVertex2f(e.p1.x * 1280, e.p1.y * 720);
		glVertex2f(e.p2.x * 1280, e.p2.y * 720);
	}
	glEnd();
}

