#pragma once
#include <GL/glew.h>

#include <SDL/SDL.h>

#include <GL/glut.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

#include "Shader.h"

class Light : public Shader
{
public:
	Light();
	~Light();

	void newLight();
};