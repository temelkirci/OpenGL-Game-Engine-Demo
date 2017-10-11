#pragma once
#include <string>
//#include <fstream>
//#include <sstream>
#include <iostream>

#include <GL/glew.h>
using namespace std;
class Shader
 {
 public:
	 Shader();
	 ~Shader();

	 GLuint Program;
	
	 Shader(const GLchar* , const GLchar* );

	 // Use the program
	 void Use();
	
 private:

 };