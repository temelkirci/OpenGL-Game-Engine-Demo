#pragma once
#include <GL/glew.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>
#include "Event.h"
#include "Camera.h"

using namespace std;

Event :: Event()
{
	yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	pitch = 0.0f;
	lastX = 1024.0f / 2.0;
	lastY = 700.0f / 2.0;
	fov = 45.0f;
	firstMouse = true;
}

Event ::~Event()
{

}

void Event :: InputEvent(GLFWwindow* pencere , Camera *cam)
{	
	double xpos, ypos;
	glfwGetCursorPos(pencere , &xpos, &ypos);
	//glfwSetCursorPos(pencere , 1024/2, 768/2);

	if(glfwGetKey(pencere, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(pencere, true);

	if(glfwGetKey(pencere, GLFW_KEY_Q) == GLFW_PRESS)
		glfwSetWindowShouldClose(pencere, true);

	if(glfwGetKey(pencere, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam -> cameraSpeed = 5.0f * cam -> deltaTime / 1000.f;
		cam -> cameraPos += cam -> cameraSpeed * cam -> cameraFront;
	}
	if(glfwGetKey(pencere, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam -> cameraSpeed = 5.0f * cam -> deltaTime / 1000.f;
		cam -> cameraPos -= glm::normalize(glm::cross(cam -> cameraFront, cam -> cameraUp)) * cam -> cameraSpeed;
	}
	if(glfwGetKey(pencere, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam -> cameraSpeed = 5.0f * cam -> deltaTime / 1000.f;
		cam -> cameraPos -= cam -> cameraSpeed * cam -> cameraFront;
	}
	if(glfwGetKey(pencere, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam -> cameraSpeed = 5.0f * cam -> deltaTime / 1000.f;
		cam -> cameraPos += glm::normalize(glm::cross(cam -> cameraFront, cam -> cameraUp)) * cam -> cameraSpeed;
	}


	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;

	if(pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cam -> cameraFront = glm::normalize(front);

}

void Event :: scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{	
	// Zoom

	if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}