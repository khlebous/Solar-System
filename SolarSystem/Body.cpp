#include "Body.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include <glm/gtc/type_ptr.hpp>

int a = 100;
float b = float(a)*2;
float c = 0.5;

Body::Body(float s, glm::vec3 color)
{
	int vertSize = 6 * 8;
	vector<float> vertices = GetCubeVertices(s, color);
	//vector<float> vertices;
	vector<int> indices;
	//GetIcosahedronVertices(s, color, &vertices, &indices);
	vertCount = vertices.size();
	//unsigned int indices[] = {  // note that we start from 0!
	//	// front
	//	0, 1, 2,
	//	2, 3, 0,
	//	// top
	//	1, 5, 6,
	//	6, 2, 1,
	//	// back
	//	7, 6, 5,
	//	5, 4, 7,
	//	// bottom
	//	4, 0, 3,
	//	3, 7, 4,
	//	// left
	//	4, 5, 1,
	//	1, 0, 4,
	//	// right
	//	3, 2, 6,
	//	6, 7, 3,
	//};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// normal attribute
	/*glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/
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
	angle =step* glfwGetTime();
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

vector<float> Body::GetCubeVertices(float s, glm::vec3 color)
{
	srand(1);

	vector<float> vert = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
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

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		// positions         // colors
		/*-1.0f*s, -1.0f*s,  1.0f*s,  (rand() % a) / b - c + color.x , (rand() % a) / b - c + color.y, (rand() % a) / b - c + color.z,
		1.0f*s, -1.0f*s,  1.0f*s, (rand() % a) / b - c + color.x , (rand() % a) / b - c + color.y, (rand() % a) / b - c + color.z,
		1.0f*s,  1.0f*s,  1.0f*s, (rand() % a) / b - c + color.x , (rand() % a) / b - c + color.y, (rand() % a) / b - c + color.z,
		-1.0f*s,  1.0f*s,  1.0f*s, (rand() % a) / b - c + color.x , (rand() % a) / b - c + color.y, (rand() % a) / b - c + color.z,
		-1.0f*s, -1.0f*s, -1.0f*s, (rand() % a) / b - c + color.x , (rand() % a) / b - c + color.y, (rand() % a) / b - c + color.z,
		1.0f*s, -1.0f*s, -1.0f*s, (rand() % a) / b - c + color.x , (rand() % a) / b - c + color.y, (rand() % a) / b - c + color.z,
		1.0f*s,  1.0f*s, -1.0f*s, (rand() % a) / b - c + color.x , (rand() % a) / b - c + color.y, (rand() % a) / b - c + color.z,
		-1.0f*s,  1.0f*s, -1.0f*s, (rand() % a) / b - c + color.x , (rand() % a) / b - c + color.y, (rand() % a) / b - c + color.z,
		/*-1.0*s, -1.0*s,  1.0*s,  error(color.x) , error(color.y), error(color.z),
		1.0*s, -1.0*s,  1.0*s,  error(color.x) , error(color.y), error(color.z),
		1.0*s,  1.0*s,  1.0*s,  error(color.x) , error(color.y), error(color.z),
		-1.0*s,  1.0*s,  1.0*s,  error(color.x) , error(color.y), error(color.z),
		-1.0*s, -1.0*s, -1.0*s,  error(color.x) , error(color.y), error(color.z),
		1.0*s, -1.0*s, -1.0*s,  error(color.x) , error(color.y), error(color.z),
		1.0*s,  1.0*s, -1.0*s,  error(color.x) , error(color.y), error(color.z),
		-1.0*s,  1.0*s, -1.0*s,  error(color.x) , error(color.y), error(color.z),*/
	};
	/*
	vector<float> vert = vector<float>();
	vert.push_back(-1.0f*s);
	vert.push_back(-1.0f*s);
	vert.push_back(1.0f*s);
	vert.push_back((rand() % a) / b - c + color.x);
	vert.push_back((rand() % a) / b - c + color.y); 
	vert.push_back((rand() % a) / b - c + color.z);
	vert.push_back(1.0f*s); 
	vert.push_back(-1.0f*s);
	vert.push_back(1.0f*s);
	vert.push_back((rand() % a) / b - c + color.x);
	vert.push_back((rand() % a) / b - c + color.y);
	vert.push_back((rand() % a) / b - c + color.z);
	vert.push_back(1.0f*s);  
	vert.push_back(1.0f*s);  
	vert.push_back(1.0f*s); 
	vert.push_back((rand() % a) / b - c + color.x); 
	vert.push_back((rand() % a) / b - c + color.y); 
	vert.push_back((rand() % a) / b - c + color.z);
	vert.push_back(-1.0f*s);
	vert.push_back(1.0f*s);  
	vert.push_back(1.0f*s);
	vert.push_back((rand() % a) / b - c + color.x); 
	vert.push_back((rand() % a) / b - c + color.y);
	vert.push_back((rand() % a) / b - c + color.z);
	vert.push_back(-1.0f*s);
	vert.push_back(-1.0f*s);
	vert.push_back(-1.0f*s);
	vert.push_back((rand() % a) / b - c + color.x); 
	vert.push_back((rand() % a) / b - c + color.y); 
	vert.push_back((rand() % a) / b - c + color.z);
	vert.push_back(1.0f*s); vert.push_back(-1.0f*s);
	vert.push_back(-1.0f*s);
	vert.push_back((rand() % a) / b - c + color.x);
	vert.push_back((rand() % a) / b - c + color.y);
	vert.push_back((rand() % a) / b - c + color.z);
	vert.push_back(1.0f*s);  
	vert.push_back(1.0f*s);
	vert.push_back(-1.0f*s);
	vert.push_back((rand() % a) / b - c + color.x); 
	vert.push_back((rand() % a) / b - c + color.y);
	vert.push_back((rand() % a) / b - c + color.z);
	vert.push_back(-1.0f*s);
	vert.push_back(1.0f*s); 
	vert.push_back(-1.0f*s);
	vert.push_back((rand() % a) / b - c + color.x); 
	vert.push_back((rand() % a) / b - c + color.y); 
	vert.push_back((rand() % a) / b - c + color.z);*/
	return vert;
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
void Body::GetIcosahedronVertices(float s, glm::vec3 color, vector<float>* v, vector<int>* idx)
{
	srand(1);
	Mesh m;
	Mesh m1;
	Mesh m2;
	Mesh m3;
	Icosahedron(m1);
	Icosahedron(m);
	/*SubdivideMesh(m1, m2);
	SubdivideMesh(m2, m3);
	SubdivideMesh(m2, m);*/
	for (auto &el : m.vertices)
		el *= s;
	vector<glm::vec3> norm = vector<glm::vec3>();
	for (size_t i = 0; i < m.vertices.size(); i+=3)
	{
		glm::vec3 a = m.vertices[i];
		glm::vec3 b = m.vertices[i+1];
		glm::vec3 c = m.vertices[i+2];
		norm.push_back(glm::normalize(glm::cross(b - a, c - a)));
	}
	for (size_t i = 0; i < m.vertices.size(); i++)
	{
		v->push_back(m.vertices[i].x);
		v->push_back(m.vertices[i].y);
		v->push_back(m.vertices[i].z);
		/*v->push_back((rand() % a) / b - c + color.x);
		v->push_back((rand() % a) / b - c + color.y);
		v->push_back((rand() % a) / b - c + color.z);*/
		v->push_back(color.x);
		v->push_back(color.y);
		v->push_back(color.z);
		int nr = i / 3;
		v->push_back(norm[nr].x);
		v->push_back(norm[nr].y);
		v->push_back(norm[nr].z);
	}
	for (size_t i = 0; i < m.triangles.size(); i++)
		idx->push_back(m.triangles[i]);
}