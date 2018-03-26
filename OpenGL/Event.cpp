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


void Event :: InputEvent(GLFWwindow* pencere , Camera cam)
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
		cam.ProcessKeyboard( FORWARD, cam.deltaTime );

		//cam -> cameraSpeed = 5.0f * cam -> deltaTime / 1000.f;
		//cam -> cameraPos += cam -> cameraSpeed * cam -> cameraFront;
	}
	if(glfwGetKey(pencere, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam.ProcessKeyboard( LEFT, cam.deltaTime );
		//cam -> cameraSpeed = 5.0f * cam -> deltaTime / 1000.f;
		//cam -> cameraPos -= glm::normalize(glm::cross(cam -> cameraFront, cam -> cameraUp)) * cam -> cameraSpeed;
	}
	if(glfwGetKey(pencere, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam.ProcessKeyboard( BACKWARD, cam.deltaTime );
		//cam -> cameraSpeed = 5.0f * cam -> deltaTime / 1000.f;
		//cam -> cameraPos -= cam -> cameraSpeed * cam -> cameraFront;
	}
	if(glfwGetKey(pencere, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam.ProcessKeyboard( RIGHT, cam.deltaTime );
		//cam -> cameraSpeed = 5.0f * cam -> deltaTime / 1000.f;
		//cam -> cameraPos += glm::normalize(glm::cross(cam -> cameraFront, cam -> cameraUp)) * cam -> cameraSpeed;
	}

	/*
	// Camera controls
    if( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera->ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera->ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera->ProcessKeyboard( LEFT, deltaTime );
    }
    
    if( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera->ProcessKeyboard( RIGHT, deltaTime );
    }
	*/
}

void Event::KeyCallback( GLFWwindow *window, Camera cam, int key, int scancode, int action, int mode )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Event::MouseCallback( GLFWwindow *window, Camera cam, double xPos, double yPos )
{
    if( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    cam.ProcessMouseMovement( xOffset, yOffset );
}

void Event::ScrollCallback( GLFWwindow *window, Camera cam, double xOffset, double yOffset )
{
    cam.ProcessMouseScroll( yOffset );
}