#include "GraphicsLibrary.h" 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
GraphicsLibrary::GraphicsLibrary()
{
}

GraphicsLibrary::~GraphicsLibrary()
{
}

void GraphicsLibrary::Draw(list<Body>* bodies, Shader ourShader)
{
	CountViewMatrix();
	CountProjMatrix();
	ourShader.setMat4("view", mView);
	ourShader.setMat4("proj", mProj);

	for (auto &b : *bodies)
	{
		//DrawBody(&b, ourShader); 
		glm::mat4 mModel = b.getMModel();
		ourShader.setMat4("model", mModel);
	//	glm::vec4 a= mProj * (mView *(mModel * glm::vec4(0.0, 0.0, 0.0, 1.0)));
		glBindVertexArray(b.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, b.VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.EBO);
		//glDrawArrays(GL_TRIANGLES, 0, 6); 
		glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
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
