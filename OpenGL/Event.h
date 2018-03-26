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

	void InputEvent(GLFWwindow*, Camera);
	
	void KeyCallback( GLFWwindow *window, Camera, int key, int scancode, int action, int mode );
	void MouseCallback( GLFWwindow *window, Camera, double xPos, double yPos );
	void ScrollCallback( GLFWwindow *window, Camera, double xOffset, double yOffset );

 private:
	GLfloat yaw;
	GLfloat pitch;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat fov;

	bool firstMouse;
 };