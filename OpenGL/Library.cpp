#include "Library.h"

using namespace glm;

static const GLint screenWidth = 1024;
static const GLint screenHeight = 700;

Library :: Library()
{

}

Library ::~Library()
{
	SDL_GL_DeleteContext(mainContext);
	SDL_DestroyWindow(mainWindow);

}

bool Library ::InitLibrary()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	// Set all the required options for SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	/* Enable multisampling for a nice antialiased effect */
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// Create our window centered at 512x512 resolution
	mainWindow = SDL_CreateWindow(
		"3D Game Engine",
		0,
		0,
		1366,
		768,
		SDL_WINDOW_OPENGL
	);

	if(mainWindow == NULL )
	{
		std::cout << "Failed to open GLFW window." << std::endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}


	mainContext = SDL_GL_CreateContext(mainWindow);

	glewExperimental = true; // Needed in core profile
	
	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// OpenGL functions will draw to window
	SDL_GL_MakeCurrent(mainWindow, mainContext);

	/* This makes our buffer swap syncronized with the monitor's vertical refresh */ // Use v-sync
	SDL_GL_SetSwapInterval(1);

	mRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	//SDL_SetRenderDrawColor(mRenderer, 200, 0, 0, 1);

	
	SDL_Log("Vendor         : %s\n", glGetString(GL_VENDOR));
	SDL_Log("Renderer       : %s\n", glGetString(GL_RENDERER));
	SDL_Log("OpenGL Version : %s\n", glGetString(GL_VERSION));
	SDL_Log("GLSL Version   : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//SDL_Log("Extensions : %s\n", glGetString(GL_EXTENSIONS));

	return EXIT_SUCCESS;
}