#pragma once
#include <GL/glew.h>

#include <GL/glut.h>

#include <SDL/SDL.h>

#include <glm/glm.hpp>

#include <iostream>

class Library
 {
 public:
	 Library();
	 ~Library();

	bool InitLibrary();

	SDL_Window* mainWindow;
	SDL_GLContext mainContext;
	SDL_Renderer* mRenderer;
 private:
	 
 };