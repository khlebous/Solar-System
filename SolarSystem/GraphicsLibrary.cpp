#include "GraphicsLibrary.h" 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
GraphicsLibrary::GraphicsLibrary()
{
}

GraphicsLibrary::~GraphicsLibrary()
{
}

void GraphicsLibrary::Draw(Sun* sun, list<Planet>* bodies, Shader sun_shader)
{
	sun_shader.use();
	sun_shader.setMat4("view", camera->GetViewMatrix());
	sun_shader.setMat4("proj", camera->GetProjMatrix());
	sun_shader.setMat4("model", sun->getMModel());
	glBindVertexArray(sun->VAO);
	glDrawArrays(GL_TRIANGLES, 0, sun->vertCount);
	//
	main_shader->use();
	main_shader->setMat4("view", camera->GetViewMatrix());
	main_shader->setMat4("proj", camera->GetProjMatrix());
	main_shader->setVec3("viewPos", *camera->cameraPosition);
	for (auto &b : *bodies)
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