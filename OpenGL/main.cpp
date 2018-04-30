#include <GL/glew.h>

#include <GL/glut.h>

#include <SDL/SDL.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <chrono>
#include <vector>

#include "Shader.h"
#include "Library.h"
#include "Camera.h"
#include "Event.h"
#include "TextureManager.h"

#include <OBJ_Loader.h>

using namespace std;

Library lib;
Camera cam;
Event ev ;

int main(int argc, char *argv[])
{
	lib.InitLibrary();
	glViewport(0, 0, 1366, 768);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader("res/shaders/core.vs", "res/shaders/core.frag");


	objl::Loader loader;
	loader.LoadFile("res/models/Test/f16.obj");

	cout << "Model was loaded" << endl;
	
	// Load Textures
	TextureManager ourTexture("res/models/Test/F16s.bmp" , 800 , 600);

	// Draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, loader.LoadedVertices.size() * sizeof(objl::Vertex), &loader.LoadedVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, loader.LoadedIndices.size() * sizeof(GLuint), &loader.LoadedIndices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (GLvoid *)0);

	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (GLvoid *)offsetof(objl::Vertex, objl::Vertex::Normal));

	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (GLvoid *)offsetof(objl::Vertex, objl::Vertex::TextureCoordinate));

	glBindVertexArray(0);

	while(!ev.mQuite)
	{	
		//auto t_start = std::chrono::high_resolution_clock::now();
		// event handling
		ev.InputEvent(cam);

		glClearColor(0.0f , 0.0f , 0.0f , 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // çizime başla
		
		ourShader.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D , ourTexture.texture);
		glUniform1i(glGetUniformLocation(ourShader.getProgramID() , "ourTexture1") , 0);

		cam.updateCamera(ourShader);

		// render models
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, loader.LoadedIndices.size(), GL_UNSIGNED_INT, 0);

		// finish render
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		SDL_GL_SwapWindow(lib.mainWindow);
	
		//auto t_now = std::chrono::high_resolution_clock::now();
		//float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		
		cam.calculateFPS(lib.mainWindow);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	SDL_Quit();

	return EXIT_SUCCESS;
}