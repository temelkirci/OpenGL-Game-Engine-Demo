#pragma once
#include <GL/glew.h>

#include <GL/glut.h>

#include <GLFW/glfw3.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

#include "Shader.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera
{
 public:
	 Camera();
	 ~Camera();

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
	void updateCameraVectors();

	glm::mat4 GetViewMatrix();
	glm::vec3 GetFront();
	glm::vec3 GetPosition();
	GLfloat GetZoom();

	//void updateCamera(Shader pShader);
	void calculateFPS(GLFWwindow* , float);
	
	float lastTime;
	float deltaTime;
	float total;
	
	 // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles
    float Yaw;
    float Pitch;

    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
 private:

 };