#include "GraphicsLibrary2.h" 
#include <glm/gtc/constants.hpp> 
 
GraphicsLibrary2::GraphicsLibrary2() 
{ 
} 
 
GraphicsLibrary2::~GraphicsLibrary2() 
{ 
} 
 
void GraphicsLibrary2::Draw(list<Body>* bodies, Shader ourShader) 
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
 
    glBindVertexArray(b.VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, b.VBO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.EBO); 
    //glDrawArrays(GL_TRIANGLES, 0, 6); 
    glDrawElements(GL_TRIANGLES, 3 *12, GL_UNSIGNED_INT, 0); 
 
    glBindVertexArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
  } 
} 
 
void GraphicsLibrary2::DrawBody(Body * body, Shader ourShader) 
{ 
} 
 
void GraphicsLibrary2::CountViewMatrix() 
{ 
  float upVecorNormal = glm::sqrt(upVector.x*upVector.x + upVector.y*upVector.y + upVector.z*upVector.z); 
  glm::vec3 upVectorVersor = glm::vec3(upVector.x / upVecorNormal, upVector.y / upVecorNormal, upVector.z / upVecorNormal); 
 
  glm::vec3 zAxis = cameraPosition - cameraTarget; 
  float zAxisNormal = glm::sqrt(zAxis.x*zAxis.x + zAxis.y*zAxis.y + zAxis.z*zAxis.z); 
  glm::vec3 zAxisVersor = glm::vec3(zAxis.x / zAxisNormal, zAxis.y / zAxisNormal, zAxis.z / zAxisNormal); 
 
  glm::vec3 xAxis = glm::vec3(upVectorVersor.y * zAxisVersor.z - upVectorVersor.z*zAxisVersor.y, 
    -upVectorVersor.x * zAxisVersor.z + upVectorVersor.z*zAxisVersor.x, 
    upVectorVersor.x*zAxisVersor.y - upVectorVersor.y*zAxisVersor.x); 
  float xAxisNormal = glm::sqrt(xAxis.x*xAxis.x + xAxis.y*xAxis.y + xAxis.z*xAxis.z); 
  glm::vec3 xAxisVersor = glm::vec3(xAxis.x / xAxisNormal, xAxis.y / xAxisNormal, xAxis.z / xAxisNormal); 
 
  glm::vec3 yAxis = glm::vec3(xAxisVersor.z * zAxisVersor.y - xAxisVersor.y*zAxisVersor.z, 
    -xAxisVersor.z * zAxisVersor.x + xAxisVersor.x*zAxisVersor.z, 
    xAxisVersor.y*zAxisVersor.x - xAxisVersor.x*zAxisVersor.y); 
 
  mView = glm::mat4(xAxisVersor.x, yAxis.x, zAxisVersor.x, cameraPosition.x, 
    xAxisVersor.y, yAxis.y, zAxisVersor.y, cameraPosition.y, 
    xAxisVersor.z, yAxis.z, zAxisVersor.z, cameraPosition.z, 
    0, 0, 0, 1); 
  mView = glm::inverse(mView); 
  //mView = glm::transpose(mView); 
} 
 
void GraphicsLibrary2::CountProjMatrix() 
{ 
  int n = 0; 
  int f = 100; 
  float fov = 45.0; 
  float a = float(720) / float(1280); 
  float e = 1.0f / tan(fov*glm::pi<float>() / 360.0); 
  mProj = glm::mat4(e, 0, 0, 0, 
    0, e / a, 0, 0, 
    0, 0, -(f + n) / (f - n), -2.0*f*n*(f - n), 
    0, 0, -1, 0); 
//  mProj = glm::transpose(mProj); 
} 
