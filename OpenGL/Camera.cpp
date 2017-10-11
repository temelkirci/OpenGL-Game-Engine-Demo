#pragma once
#include <GL/glew.h>
#include <GL/glut.h>

#include <GL/glut.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"
#include <string>
#include <iostream>

using namespace glm;
using namespace std;

Camera :: Camera()
{
	cameraSpeed = 0.05f;

	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	lastTime = 0;
	deltaTime = 0;
	total = 0;
}

Camera ::~Camera()
{

}

void Camera :: updateCamera(Shader ourShader)
{
	/*
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	*/

	GLfloat radius = 10.0f;
	GLdouble camX = sin(glfwGetTime()) * radius;
	GLdouble camZ = cos(glfwGetTime()) * radius;

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	// Create transformations
	
    projection = glm::perspective(45.0f, 1024.0f / 700.0f, 0.1f, 100.0f);

    // Get their uniform location
    modelLoc = glGetUniformLocation(ourShader.Program, "model");
    viewLoc = glGetUniformLocation(ourShader.Program, "view");
    projLoc = glGetUniformLocation(ourShader.Program, "projection");

    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    // Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

}

void Camera :: calculateFPS(GLFWwindow* pencere , double startTime)
{
	lastTime = glfwGetTime();

	deltaTime = (lastTime - startTime)*1000.0;
			
	total += deltaTime;

	if(total >= 250.0)
	{
		glfwSetWindowTitle (pencere, (to_string(int(1000 / deltaTime))).c_str());
		total = 0;
		//glfwSetTime(0.0);
	}
}