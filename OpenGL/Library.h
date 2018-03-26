#pragma once
#include <GL/glew.h>

#include <GL/glut.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>

class Library
 {
 public:
	 Library();
	 ~Library();

	bool InitLibrary();
	GLFWwindow* window;
 private:

 };