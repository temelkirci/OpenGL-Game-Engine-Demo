#include "Camera.h"
#include "Shader.h"

using namespace glm;
using namespace std;

Camera :: Camera()
{
	cameraSpeed = 0.05f;
	zoom = 45.0f;
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	

	firstTime = 0;
	lastTime = 0;
	deltaTime = 0;

	totalTime = 0;

	yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
	pitch = 0.0f;
	lastX = 1024.0f / 2.0;
	lastY = 700.0f / 2.0;
	fov = 45.0f;
	firstMouse = true;
}

Camera ::~Camera()
{

}

void Camera::updateCamera(Shader pShader)
{
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	
	GLfloat radius = 10.0f;
	GLdouble camX = sin(SDL_GetTicks()) * radius;
	GLdouble camZ = cos(SDL_GetTicks()) * radius;

	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(GetZoom()), (float)1024 / (float)700, 0.1f, 100.0f);
	pShader.setMat4("projection", projection);

	// camera/view transformation
	glm::mat4 view = GetViewMatrix();
	pShader.setMat4("view", view);
	
}


void Camera :: calculateFPS(SDL_Window* pencere)
{
	lastTime = SDL_GetTicks();

	deltaTime = (lastTime - firstTime);
	
	firstTime = SDL_GetTicks();
	totalTime += deltaTime;

	if (totalTime > 250)
	{
		SDL_SetWindowTitle(pencere, (to_string(int(1000/deltaTime))).c_str());
		totalTime = 0;
	}
}

void Camera::inputMouse(int pX, int pY)
{
	if (firstMouse)
	{
		lastX = pX;
		lastY = pY;
		firstMouse = false;
	}

	GLfloat xoffset = pX - lastX;
	GLfloat yoffset = lastY - pY;

	lastX = pX;
	lastY = pY;

	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
  
GLfloat Camera::GetZoom()
{
	return this->zoom;
}
   
glm::vec3 Camera::GetPosition()
{
	return this->cameraPos;
}
    
glm::vec3 Camera::GetFront()
{
	return this->cameraFront;
}