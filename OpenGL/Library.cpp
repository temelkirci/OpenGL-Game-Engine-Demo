#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include "Library.h"
#include <iostream>

using namespace glm;

static const int screenWidth = 1024;
static const int screenHeight = 700;

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
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return 0;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	window = glfwCreateWindow( 1024, 700, "3D OpenGL Game Engine", NULL, NULL);

	if( window == NULL )
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		system("pause");
		glfwTerminate();
		return 0;
	}


	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental=true; // Needed in core profile
	
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		system("pause");
		return 0;
	}

	//std::cout<<"Opengl version :"<<glGetString(GL_VERSION)<< std::endl;
	//std::cout<<"GLSL version :"<<glGetString(GL_SHADING_LANGUAGE_VERSION)<< std::endl;
	//std::cout<<"Opengl Renderer :"<<glGetString(GL_RENDERER)<< std::endl;
	//std::cout<<"Opengl Vendor :"<<glGetString(GL_VENDOR)<< std::endl<<std::endl;

	return 1;
	exit(0);
}