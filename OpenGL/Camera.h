#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include "Shader.h"

class Camera
{
 public:
	 Camera();
	 ~Camera();

	void updateCamera(Shader);
	void calculateFPS(GLFWwindow* , double);

	double lastTime;
	double deltaTime;
	double total;
	
	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;

	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	glm::vec3 cameraPos;
	GLfloat cameraSpeed;

	glm::mat4 view;
    glm::mat4 projection;
 private:

 };