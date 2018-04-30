#pragma once
#include <GL/glew.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <iostream>

#include "Event.h"
#include "Camera.h"

using namespace std;

Event :: Event()
{
	//Enable text input
	//SDL_StartTextInput();
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);

	mQuite = false;
}

Event ::~Event()
{
	//SDL_StopTextInput();
}


void Event :: InputEvent(Camera cam)
{		
	int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);

	GLfloat cameraSpeed = 5.0f;

	while (SDL_PollEvent(&mKey))
	{
		switch (mKey.type)
		{
			//User requests quit
			case SDL_QUIT:
				mQuite = true;

				break;
			
			case SDL_MOUSEMOTION:
				//GLfloat xOffset, yOffset;
				//xOffset = mKey.motion.xrel;
				//yOffset = mKey.motion.yrel;

				//cam.inputMouse(xpos, ypos);
				//cam.scroll(mKey.motion.xrel, mKey.motion.yrel);
				break;
				
			case SDL_KEYDOWN:
				switch (mKey.key.keysym.sym)
				{
					case SDLK_w:
						
						cam.cameraPos = cam.cameraPos + cameraSpeed * cam.cameraFront;
						std::cout << "ileri : " << cam.cameraPos.x << "   " << cam.cameraPos.y << "   " << cam.cameraPos.z << "   " << std::endl;
						break;
					case SDLK_s:
						
						cam.cameraPos = cam.cameraPos - cameraSpeed * cam.cameraFront;
						std::cout << "geri : " << cam.cameraPos.x << "   " << cam.cameraPos.y << "   " << cam.cameraPos.z << "   " << std::endl;
						break;
					case SDLK_a:
						
						cam.cameraPos = cam.cameraPos - glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cameraSpeed;
						std::cout << "sola : " << cam.cameraPos.x << "   " << cam.cameraPos.y << "   " << cam.cameraPos.z << "   " << std::endl;
						break;
					case SDLK_d:
						
						cam.cameraPos = cam.cameraPos + glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cameraSpeed;
						std::cout << "sağa : " << cam.cameraPos.x << "   " << cam.cameraPos.y << "   " << cam.cameraPos.z << "   " << std::endl;
						break;

					case SDLK_TAB:
						//std::this_thread::sleep_for(std::chrono::seconds(5)); // wait for 5 seconds
						mQuite = true;
						break;
				}
			
		}
	}
}