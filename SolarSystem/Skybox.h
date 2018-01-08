#pragma once
#include <vector>

#include "shader_m.h"
using namespace std;

class Skybox
{
public:
	Skybox();
	~Skybox();

	unsigned int skyboxVAO, skyboxVBO;
	Shader skyboxShader;
	unsigned int cubemapTexture;

	void Draw(glm::mat4 viewM, glm::mat4 projM);
private:
	unsigned int loadCubemap(vector<std::string> faces);
};

