#include "Body.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


Body::Body(float s, glm::vec3 color)
{
	name = "body";
	this->color = color;
	this->scale = s;
	GetIcosahedronVertices(s, color, &vertices);
	vertCount = vertices.size()/9;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	UpdateBuffers();
}

Body::~Body()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	vertices.clear();
}

void Body::SetColor()
{
	int aa = 100;
	float bb = float(aa) * 2.0;
	float cc = float(aa) / bb / 2.0;
	vector<float> colors = vector<float>(vertCount);
	for (size_t i = 6; i < vertices.size(); i+=9)
	{
		vertices[i] = color.x;
		vertices[i+1] = color.y;
		//vertices[i+2] = color.z;
		//vertices[i ] = (rand() % aa) / bb - cc + color.x;
		//vertices[i + 1] = (rand() % aa) / bb - cc + color.y;
		vertices[i + 2] = (rand() % aa) / bb - cc + color.z;
	}
	UpdateBuffers();
}

void Body::SetScale()
{
	for (size_t i = 0; i < m.triangles.size(); i++)
	{
		int t1 = m.triangles[i];
		vertices[9 * i] = m.vertices[t1].x*scale;
		vertices[9 * i + 1] = m.vertices[t1].y*scale;
		vertices[9 * i + 2] = m.vertices[t1].z*scale;
	}
	Body::UpdateBuffers();
}

void Body::UpdateBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Body::Icosahedron(Mesh & mesh)
{
	const double t = (1.0 + std::sqrt(5.0)) / 2.0;

	// Vertices
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(-1.0, t, 0.0)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(1.0, t, 0.0)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(-1.0, -t, 0.0)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(1.0, -t, 0.0)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(0.0, -1.0, t)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(0.0, 1.0, t)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(0.0, -1.0, -t)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(0.0, 1.0, -t)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(t, 0.0, -1.0)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(t, 0.0, 1.0)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(-t, 0.0, -1.0)));
	mesh.vertices.emplace_back(glm::normalize(glm::vec3(-t, 0.0, 1.0)));

	// Faces
	mesh.addTriangle(0, 11, 5);
	mesh.addTriangle(0, 5, 1);
	mesh.addTriangle(0, 1, 7);
	mesh.addTriangle(0, 7, 10);
	mesh.addTriangle(0, 10, 11);
	mesh.addTriangle(1, 5, 9);
	mesh.addTriangle(5, 11, 4);
	mesh.addTriangle(11, 10, 2);
	mesh.addTriangle(10, 7, 6);
	mesh.addTriangle(7, 1, 8);
	mesh.addTriangle(3, 9, 4);
	mesh.addTriangle(3, 4, 2);
	mesh.addTriangle(3, 2, 6);
	mesh.addTriangle(3, 6, 8);
	mesh.addTriangle(3, 8, 9);
	mesh.addTriangle(4, 9, 5);
	mesh.addTriangle(2, 4, 11);
	mesh.addTriangle(6, 2, 10);
	mesh.addTriangle(8, 6, 7);
	mesh.addTriangle(9, 8, 1);
}

uint32_t subdivideEdge(uint32_t f0, uint32_t f1, const glm::vec3 &v0, const glm::vec3 &v1, Mesh &io_mesh, std::map<Edge, uint32_t> &io_divisions)
{
	const Edge edge(f0, f1);
	auto it = io_divisions.find(edge);
	if (it != io_divisions.end())
	{
		return it->second;
	}

	const glm::vec3 v = glm::normalize(glm::vec3(0.5) * (v0 + v1));
	const uint32_t f = io_mesh.vertices.size();
	io_mesh.vertices.emplace_back(v);
	io_divisions.emplace(edge, f);
	return f;
}
void SubdivideMesh(const Mesh &meshIn, Mesh &meshOut)
{
	meshOut.vertices = meshIn.vertices;

	std::map<Edge, uint32_t> divisions; // Edge -> new vertex

	for (uint32_t i = 0; i < meshIn.triangleCount(); ++i)
	{
		const uint32_t f0 = meshIn.triangles[i * 3];
		const uint32_t f1 = meshIn.triangles[i * 3 + 1];
		const uint32_t f2 = meshIn.triangles[i * 3 + 2];

		const glm::vec3 v0 = meshIn.vertices[f0];
		const glm::vec3 v1 = meshIn.vertices[f1];
		const glm::vec3 v2 = meshIn.vertices[f2];

		const uint32_t f3 = subdivideEdge(f0, f1, v0, v1, meshOut, divisions);
		const uint32_t f4 = subdivideEdge(f1, f2, v1, v2, meshOut, divisions);
		const uint32_t f5 = subdivideEdge(f2, f0, v2, v0, meshOut, divisions);

		meshOut.addTriangle(f0, f3, f5);
		meshOut.addTriangle(f3, f1, f4);
		meshOut.addTriangle(f4, f2, f5);
		meshOut.addTriangle(f3, f4, f5);
	}
}
void Body::GetIcosahedronVertices(float s, glm::vec3 color, vector<float>* v)
{
	int aa = 100;
	float bb = float(aa) * 2.0;
	float cc = float(aa) / bb / 2.0;
	srand(1);
	
	Mesh m1;
	Mesh m2;
	Mesh m3;
	Mesh m4;
	Icosahedron(m1);
	//Icosahedron(m);
	SubdivideMesh(m1, m2);
	SubdivideMesh(m2, m);
	//SubdivideMesh(m3, m4);
	//SubdivideMesh(m4, m);
	/*for (auto &el : m.vertices)
		el *= s;
*/
	for (size_t i = 0; i < m.triangles.size(); i += 3)
	{
		int t1 = m.triangles[i];
		int t2 = m.triangles[i + 1];
		int t3 = m.triangles[i + 2];
		glm::vec3 a = m.vertices[t1];
		glm::vec3 b = m.vertices[t2];
		glm::vec3 c = m.vertices[t3];
	//	glm::vec3 norm = glm::normalize(glm::cross(b - a, c - a));
		vector<float> colors = vector<float>(m.vertices.size());
		for (size_t i = 0; i < m.vertices.size(); i++)
		{
			colors[i] = (rand() % aa) / bb - cc + color.z;
		}
		v->push_back(m.vertices[t1].x*s);
		v->push_back(m.vertices[t1].y*s);
		v->push_back(m.vertices[t1].z*s);
		/*v->push_back(norm.x);
		v->push_back(norm.y);
		v->push_back(norm.z);*/
		v->push_back(a.x);
		v->push_back(a.y);
		v->push_back(a.z);
		v->push_back(color.x);
		v->push_back(color.y);
		//v->push_back(color.z);
		v->push_back(colors[t1]);

		v->push_back(m.vertices[t2].x*s);
		v->push_back(m.vertices[t2].y*s);
		v->push_back(m.vertices[t2].z*s);
		/*v->push_back(norm.x);
		v->push_back(norm.y);
		v->push_back(norm.z);*/
		v->push_back(b.x);
		v->push_back(b.y);
		v->push_back(b.z);
		v->push_back(color.x);
		v->push_back(color.y);
		//v->push_back(color.z);
		v->push_back(colors[t2]);

		v->push_back(m.vertices[t3].x*s);
		v->push_back(m.vertices[t3].y*s);
		v->push_back(m.vertices[t3].z*s);
		/*v->push_back(norm.x);
		v->push_back(norm.y);
		v->push_back(norm.z);*/
		v->push_back(c.x);
		v->push_back(c.y);
		v->push_back(c.z);
		v->push_back(color.x);
		v->push_back(color.y);
		//v->push_back(color.z);
		v->push_back(colors[t3]);
	}
}
