#pragma once
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <SOIL2/SOIL2.h>
#include <SOIL2/stb_image.h>

#include <iostream>

class Texture
 {
 public:
	 Texture();
	 ~Texture();

	Texture(const char* pTexturePath1 , int width , int height);
	GLuint texture;
 private:
	 
 };