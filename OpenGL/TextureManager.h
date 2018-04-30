#pragma once
#include <GL/glew.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>

using namespace std;

class TextureManager
 {
 public:
	 TextureManager();
	 ~TextureManager();

	 TextureManager(const char* pTexturePath1 , int width , int height);
	GLuint texture;
 private:
	 
 };