#pragma once
#include <GL/glew.h>

#include <GL/glut.h>

#include <SDL/SDL.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp> // functions to ease the calculation of the view and projection matrices.
#include <glm/gtc/type_ptr.hpp> // adds functionality for converting a matrix object into a float array for usage in OpenGL.
#include <glm/glm.hpp>

#include <string>
#include <iostream>

#include "Shader.h"

class Camera
{
 public:
	 Camera();
	 ~Camera();

	glm::mat4 GetViewMatrix();
	glm::vec3 GetFront();
	glm::vec3 GetPosition();
	GLfloat GetZoom();

	void updateCamera(Shader pShader);
	void calculateFPS(SDL_Window*);
	void inputMouse(int pX, int pY);

	float firstTime;
	float lastTime;
	float deltaTime;
	float totalTime;
	
	float cameraSpeed;
	float zoom;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	GLfloat yaw;
	GLfloat pitch;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat fov;

	bool firstMouse;
 private:

 };