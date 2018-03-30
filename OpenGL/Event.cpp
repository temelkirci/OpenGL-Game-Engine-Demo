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
	SDL_StartTextInput();

	mQuite = false;
}

Event ::~Event()
{
	SDL_StopTextInput();
}


void Event :: InputEvent(Camera cam)
{		
	int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);

	while (SDL_PollEvent(&mKey))
	{
		switch (mKey.type)
		{
			//User requests quit
			case SDL_QUIT:
				mQuite = true;
				break;
			
			case SDL_MOUSEMOTION:
				//cam.cameraFront = MouseMotion(xpos, ypos);
				break;

			case SDL_KEYDOWN:
				switch (mKey.key.keysym.sym)
				{
					case SDLK_w:
						std::cout << " You pressed w key " << std::endl;
						cam.cameraPos += cam.cameraSpeed * cam.cameraFront;
						break;
					case SDLK_s:
						std::cout << " You pressed s key " << std::endl;
						cam.cameraPos -= cam.cameraSpeed * cam.cameraFront;
						break;
					case SDLK_a:
						std::cout << " You pressed a key " << std::endl;
						cam.cameraPos -= glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cam.cameraSpeed;
						break;
					case SDLK_d:
						std::cout << " You pressed d key " << std::endl;
						cam.cameraPos += glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cam.cameraSpeed;
						break;

					case SDLK_TAB:
						//std::this_thread::sleep_for(std::chrono::seconds(5));
						mQuite = true;
						break;
				}
			
		}
	}
}

/*
void Event::MouseCallback( GLFWwindow *window, Camera cam, double xPos, double yPos )
{
    if( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    cam.ProcessMouseMovement( xOffset, yOffset );
}

void Event::ScrollCallback( GLFWwindow *window, Camera cam, double xOffset, double yOffset )
{
    cam.ProcessMouseScroll( yOffset );
}
*/
