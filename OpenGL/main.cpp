#include <GL/glew.h>

#include <GL/glut.h>

#include <GLFW/glfw3.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Shader.h"
#include "Library.h"
#include "Camera.h"
#include "Event.h"
#include "Texture.h"

using namespace std;

Library lib;
Camera cam;
Event ev ;

int main()
{
	lib.InitLibrary();
	glViewport(0, 0, 1024, 700);

	glEnable(GL_DEPTH_TEST || GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

	glfwSetInputMode(lib.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Set the required callback functions
    glfwSetKeyCallback( lib.window, ev.KeyCallback );
    glfwSetCursorPosCallback( lib.window, ev.MouseCallback );
    glfwSetScrollCallback( lib.window, ev.ScrollCallback );

	Shader ourShader("res/shaders/core.vs", "res/shaders/core.frag");

	
   // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = 
	{
		// Positions			// Colors               // Texture Coordinates
        0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // Top - Right
        0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,		1.0f, 0.0f, // Bottom - Right
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Bottom - Left
		-0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 1.0f,		0.0f, 1.0f  // Top - Left
    };

	GLuint indices[]=
	{
		0, 1, 3, // 1.Triangle
		1, 2, 3  // 2.Triangle
	};
	 
    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8  * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
   
	// Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8  * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

	// Texture Coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8  * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// Load Textures
	Texture ourTexture("res/textures/box1.png" , 400 , 400);

	glfwSetInputMode(lib.window, GLFW_STICKY_KEYS, GL_TRUE);
	
	while(!(glfwWindowShouldClose(lib.window)))
	{
		glfwPollEvents();
		float firstTime = glfwGetTime();

		// event handling
		ev.InputEvent(lib.window , cam);

		glClearColor(0.2f , 0.3f , 0.3f , 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // çizime başla
		
		ourShader.Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D , ourTexture.texture);
		glUniform1i(glGetUniformLocation(ourShader.getProgramID() , "ourTexture") , 0);

		glm::mat4 projection;
        projection = glm::perspective(cam.GetZoom(), (GLfloat)1024/(GLfloat)700, 0.1f, 1000.0f);
        
        // Create camera transformation
        glm::mat4 view;
        view = cam.GetViewMatrix( );

        // Get the uniform locations
		GLint modelLoc = glGetUniformLocation( ourShader.getProgramID(), "model" );
        GLint viewLoc = glGetUniformLocation( ourShader.getProgramID(), "view" );
        GLint projLoc = glGetUniformLocation( ourShader.getProgramID(), "projection" );
        
        // Pass the matrices to the shader
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0);
		glBindVertexArray(0);

		//cam->updateCamera(ourShader);

		glfwSwapBuffers(lib.window); // çizimi bitir
		
		cam.calculateFPS(lib.window , firstTime);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

	return EXIT_SUCCESS;
}