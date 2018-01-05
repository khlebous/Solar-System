#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Planet.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
enum Camera_Mode {
	STATIC,
	FOLLOWING_PLANET
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVTY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	// Camera Attributes
	glm::vec3* Position;
	glm::vec3* Front; //cameraTarget - cameraPosition
	glm::vec3* Up;
	glm::vec3* Right;
	glm::vec3* WorldUp;
	// Eular Angles
	float* Yaw;
	float* Pitch;
	// Camera options
	float* MovementSpeed;
	float* MouseSensitivity;
	float* Zoom;

	int* WINDOW_WIDTH;
	int* WINDOW_HEIGHT;

	Camera_Mode Mode;

	/*glm::vec3* cameraPosition;
	glm::vec3* cameraTarget;
	glm::vec3* cameraFront;
	glm::vec3* upVector;*/

	Planet *planet;
private:
	float n;
	float f;

public:
	Camera()
	{
		n = 0.01;
		f = 20.0;
		Mode = STATIC;
	}
	// Constructor with vectors
	//Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(	), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	//{
	//	/*Position = position;
	//	WorldUp = up;
	//	Yaw = yaw;
	//	Pitch = pitch;
	//	updateCameraVectors();*/

	//	n = 0.01;
	//	f = 20.0;
	//	Mode = STATIC;
	//}
	// Constructor with scalar values
	//Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	///{
		/*Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();*/
	//}

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
	//	return glm::lookAt(*Position, *Position + *Front, *Up);
		glm::vec3 upVec = glm::normalize(glm::make_vec3(*Up));
		glm::vec3 zAxis;
		if (STATIC == Mode)
			zAxis = glm::normalize(-*Front); // camDirection
		else if (FOLLOWING_PLANET == Mode)
			zAxis = glm::normalize(*Position - planet->getCenterPosition()); // camDirection
		glm::vec3 xAxis = glm::normalize(glm::cross(upVec, zAxis)); //cam Right
		glm::vec3 yAxis = glm::cross(zAxis, xAxis);

		return glm::transpose(
			glm::inverse(
				glm::mat4(
					xAxis.x, yAxis.x, zAxis.x, (*Position).x,
					xAxis.y, yAxis.y, zAxis.y, (*Position).y,
					xAxis.z, yAxis.z, zAxis.z, (*Position).z,
					0, 0, 0, 1)));
	}
	glm::mat4 GetProjMatrix()
	{
		float a = float(*WINDOW_HEIGHT) / float(*WINDOW_WIDTH);
		float e = 1.0f / tan(glm::radians(*Zoom) / 2);
		return  glm::transpose(glm::mat4(e, 0, 0, 0,
			0, e / a, 0, 0,
			0, 0, -(f + n) / (f - n), -2.0*f*n / (f - n),
			0, 0, -1, 0));
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		/*float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			*cameraPosition += (*cameraTarget - *cameraPosition) * velocity;
		if (direction == BACKWARD)
			*cameraPosition -= (*cameraTarget - *cameraPosition) * velocity;
*/
		float velocity = *MovementSpeed * deltaTime;
		if (direction == FORWARD)
			*Position += *Front * velocity;
		if (direction == BACKWARD)
			*Position -= *Front * velocity;
		if (direction == LEFT)
			*Position -= *Right * velocity;
		if (direction == RIGHT)
			*Position += *Right * velocity;
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= *MouseSensitivity;
		yoffset *= *MouseSensitivity;

		*Yaw += xoffset;
		*Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (*Pitch > 89.0f)
				*Pitch = 89.0f;
			if (*Pitch < -89.0f)
				*Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (*Zoom >= 1.0f && *Zoom <= 45.0f)
			*Zoom -= yoffset;
		if (*Zoom <= 1.0f)
			*Zoom = 1.0f;
		if (*Zoom >= 45.0f)
			*Zoom = 45.0f;
	}

	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(*Yaw)) * cos(glm::radians(*Pitch));
		front.y = sin(glm::radians(*Pitch));
		front.z = sin(glm::radians(*Yaw)) * cos(glm::radians(*Pitch));
		*Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		*Right = glm::normalize(glm::cross(*Front, *WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		*Up = glm::normalize(glm::cross(*Right, *Front));
	}
};
#endif