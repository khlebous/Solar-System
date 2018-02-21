#include "GraphicsLibrary.h" 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>

void GraphicsLibrary::Draw()
{
	glm::mat4 viewM = camera->GetViewMatrix();
	glm::mat4 projM = camera->GetProjMatrix();
	ss->Draw(viewM, projM, camera->Position, camera->Front);
}