#include "Sun.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include <glm/gtc/type_ptr.hpp>

Sun::Sun(float s, glm::vec3 color) :Body(s, color) 
{
}

Sun::~Sun()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

glm::mat4 Sun::getMModel()
{
	angle = step * glfwGetTime();
	mModel = glm::mat4(
		cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	mModel = glm::transpose(mModel);
	return mModel;
}

void Sun::SetColor()
{
	int aa = 100;
	float bb = float(aa) * 2.0;
	float cc = float(aa) / bb / 2.0;
	vector<float> colors = vector<float>(vertCount);
	for (size_t i = 6; i < vertices.size(); i += 9)
	{
		vertices[i] = color.x;
		vertices[i + 1] = color.y;
		//vertices[i ] = (rand() % aa) / bb - cc + color.x;
		//vertices[i + 1] = (rand() % aa) / bb - cc + color.y;
		if (rand() % 2 == 0)
			vertices[i + 2] = (rand() % aa) / bb - cc + color.z;
		else
			vertices[i + 2] = color.z;
	}
	SetSunColorToShader();
	Body::UpdateBuffers();
}
void Sun::SetScale()
{
	for (size_t i = 0; i < m.triangles.size(); i++)
	{
		int t1 = m.triangles[i];
		vertices[9*i] = m.vertices[t1].x*scale;
		vertices[9*i+1] = m.vertices[t1].y*scale;
		vertices[9*i+2] = m.vertices[t1].z*scale;
	}
	Body::UpdateBuffers();
}
void Sun::SetSunColorToShader()
{
	shader->use();
	shader->setVec3("lightColor", color);
	glUseProgram(0);
}
//
//void Sun::GetIcosahedronVertices(float s, glm::vec3 color, vector<float>* v)
//{
//	srand(1);
//	Mesh m;
//	Mesh m1;
//	Mesh m2;
//	Mesh m3;
//	Mesh m4;
//	Icosahedron(m1);
//	//Icosahedron(m);
//	SubdivideMesh2(m1, m2);
//	SubdivideMesh2(m2, m);
//	//SubdivideMesh2(m1, m);
//	for (auto &el : m.vertices)
//		el *= s;
//
//	for (size_t i = 0; i < m.triangles.size(); i += 3)
//	{
//		int t1 = m.triangles[i];
//		int t2 = m.triangles[i + 1];
//		int t3 = m.triangles[i + 2];
//		glm::vec3 a = m.vertices[t1];
//		glm::vec3 b = m.vertices[t2];
//		glm::vec3 c = m.vertices[t3];
//		glm::vec3 norm = glm::normalize(glm::cross(b - a, c - a));
//
//		vector<float> colors = vector<float>(m.vertices.size());
//		for (size_t i = 0; i < m.vertices.size(); i++)
//		{
//			colors[i] = (rand() % aaaa) / bbbb - cccc + color.z;
//		}
//
//		v->push_back(m.vertices[t1].x);
//		v->push_back(m.vertices[t1].y);
//		v->push_back(m.vertices[t1].z);
//		v->push_back(norm.x);
//		v->push_back(norm.y);
//		v->push_back(norm.z);
//		v->push_back(color.x);
//		v->push_back(color.y);
//		v->push_back(colors[t1]);
//
//		v->push_back(m.vertices[t2].x);
//		v->push_back(m.vertices[t2].y);
//		v->push_back(m.vertices[t2].z);
//		v->push_back(norm.x);
//		v->push_back(norm.y);
//		v->push_back(norm.z);
//		v->push_back(color.x);
//		v->push_back(color.y); 
//		v->push_back(colors[t2]);
//
//		v->push_back(m.vertices[t3].x);
//		v->push_back(m.vertices[t3].y);
//		v->push_back(m.vertices[t3].z);
//		v->push_back(norm.x);
//		v->push_back(norm.y);
//		v->push_back(norm.z);
//		v->push_back(color.x);
//		v->push_back(color.y); 
//		v->push_back(colors[t3]);
//	}
//}
