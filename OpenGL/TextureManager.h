#pragma once
#include <GL/glew.h>

#include <SDL/SDL.h>

#include <SOIL2/SOIL2.h>
#include <SOIL2/stb_image.h>

#include <iostream>

class TextureManager
 {
 public:
	 TextureManager();
	 ~TextureManager();

	 TextureManager(const char* pTexturePath1 , int width , int height);
	GLuint texture;
 private:
	 
 };