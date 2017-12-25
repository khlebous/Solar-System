#include "Sun.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include <glm/gtc/type_ptr.hpp>
int aaaa = 100;
float bbbb = float(aaaa) * 2;
float cccc = 0.5;

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
