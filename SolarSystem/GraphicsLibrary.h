#pragma once
#include <iostream>
#include <list>
#include <glm/mat4x4.hpp> // glm::mat4

#include "Edge.h"
#include "Body.h"
#include "shader_m.h"
using namespace std;
namespace GL
{
	void Draw(list<Body>* edges, Shader ourShader);
	void DrawBody(Body* body, Shader ourShader);
}
/*mModel = glm::mat4(
1, 0, 0, 0,
0, cos(angle), -sin(angle), 0,
0, sin(angle), cos(angle), 0,
0, 0, 0, 1);*/
/*mModel = glm::mat4(
cos(angle), 0, sin(angle), 0,
0, 1, 0, 0,
-sin(angle),0, cos(angle), 0,
0, 0, 0, 1);*/