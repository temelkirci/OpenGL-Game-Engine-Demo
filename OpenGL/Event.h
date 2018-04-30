#pragma once
#include <SDL/SDL.h>

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

	bool mQuite;
	void InputEvent(Camera);
	glm::vec3 MouseMotion(float x, float y);

	SDL_Event mKey;
 private:

 };