#include "GraphicsLibrary.h" 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
GraphicsLibrary::GraphicsLibrary()
{
}

GraphicsLibrary::~GraphicsLibrary()
{
}

void GraphicsLibrary::Draw(Sun* sun, list<Planet>* planets)
{
	glm::mat4 viewM = camera->GetViewMatrix();
	glm::mat4 projM = camera->GetProjMatrix();

	sun->Draw(viewM, projM);
	//
	main_shader->use();
	main_shader->setMat4("view", camera->GetViewMatrix());
	main_shader->setMat4("proj", camera->GetProjMatrix());
	main_shader->setVec3("viewPos", camera->Position);
	for (auto &b : *planets)
	{
		main_shader->setMat4("model", b.getMModel());
		glBindVertexArray(b.VAO);
		glDrawArrays(GL_TRIANGLES, 0, b.vertCount);
		//glDrawElements(GL_TRIANGLES, b.vertCount/2, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 3 * 1, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
	glUseProgram(0);
}