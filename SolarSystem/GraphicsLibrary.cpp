#include "GraphicsLibrary.h" 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
GraphicsLibrary::GraphicsLibrary()
{
}

GraphicsLibrary::~GraphicsLibrary()
{
}

void GraphicsLibrary::Draw(Sun* sun, list<Planet>* bodies, Shader ourShader, Shader sun_shader)
{
	CountViewMatrix();
	CountProjMatrix();
	//
	sun_shader.use();
	sun_shader.setMat4("view", mView);
	sun_shader.setMat4("proj", mProj);
	sun_shader.setMat4("model", sun->getMModel());
	glBindVertexArray(sun->VAO);
	glDrawArrays(GL_TRIANGLES, 0, sun->vertCount);
	//

	ourShader.use();
	ourShader.setMat4("view", mView);
	ourShader.setMat4("proj", mProj);
	for (auto &b: *bodies)
	{
		ourShader.setMat4("model", b.getMModel());
		glBindVertexArray(b.VAO);
		glDrawArrays(GL_TRIANGLES, 0, b.vertCount); 
		//glDrawElements(GL_TRIANGLES, b.vertCount/2, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 3 * 1, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
	glUseProgram(0);
}

void GraphicsLibrary::DrawBody(Body * body, Shader ourShader)
{
}

void GraphicsLibrary::CountViewMatrix()
{
	glm::vec3 upVec = glm::normalize(glm::make_vec3(*upVector));
	glm::vec3 zAxis = glm::normalize(*cameraPosition - *cameraTarget); // camDirection
	glm::vec3 xAxis = glm::normalize(glm::cross(upVec, zAxis)); //cam Right
	glm::vec3 yAxis = glm::cross(zAxis, xAxis);

	mView = glm::mat4(xAxis.x, yAxis.x, zAxis.x, (*cameraPosition).x,
		xAxis.y, yAxis.y, zAxis.y, (*cameraPosition).y,
		xAxis.z, yAxis.z, zAxis.z, (*cameraPosition).z,
		0, 0, 0, 1);
	mView = glm::inverse(mView);
	mView = glm::transpose(mView); 
}

void GraphicsLibrary::CountProjMatrix()
{
	float n = 1;
	float f = 100;
	float fov = 45.0;
	float a = float(*WINDOW_HEIGHT) / float(*WINDOW_WIDTH);
	float e = 1.0f / tan(fov*glm::pi<float>() / 360.0);
	mProj = glm::mat4(e, 0, 0, 0,
		0, e / a, 0, 0,
		0, 0, -(f + n) / (f - n), -2.0*f*n / (f - n),
		0, 0, -1, 0);
	  mProj = glm::transpose(mProj); 
}
