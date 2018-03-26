#include "Library.h"

using namespace glm;

static const GLint screenWidth = 1024;
static const GLint screenHeight = 700;

Library :: Library()
{

}

Library ::~Library()
{

}

bool Library ::InitLibrary()
{
	if( !glfwInit() )
	{
		std::cout <<  "Failed to initialize GLFW" << std::endl;
		return EXIT_FAILURE;
	}

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
	#endif

	window = glfwCreateWindow( screenWidth, screenHeight, "3D OpenGL Game Engine", nullptr, nullptr);

	if( window == NULL )
	{
		std::cout << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}


	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	
	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout<<"Opengl version :"<<glGetString(GL_VERSION)<< std::endl;
	std::cout<<"GLSL version :"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<< std::endl;
	std::cout<<"Opengl Renderer :"<<glGetString(GL_RENDERER)<< std::endl;
	std::cout<<"Opengl Vendor :"<<glGetString(GL_VENDOR)<< std::endl<<std::endl;

	return EXIT_SUCCESS;
}