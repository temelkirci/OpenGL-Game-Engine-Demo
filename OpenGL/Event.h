#pragma once
#include <GLFW/glfw3.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "Camera.h"

class Event
 {
 public:
	 Event();
	 ~Event();

	void InputEvent(GLFWwindow* , Camera*);
	void   scroll_callback(GLFWwindow* , double , double );

	GLfloat yaw;
	GLfloat pitch;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat fov;

	bool firstMouse;
	
 private:
	 
 };