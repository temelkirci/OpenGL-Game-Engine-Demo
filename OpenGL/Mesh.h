#pragma once

#include <GL/glew.h>

#include <GL/glut.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "Shader.h"

using namespace std;

struct Vertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture 
{
	GLuint id;
	string type;
};

class Mesh 
{
public:
	/* Mesh Data */
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	/* Functions */
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void Draw(Shader shader);
private:
	/* Render data */
	GLuint VAO, VBO, EBO;
	/* Functions */
	void setupMesh();
};