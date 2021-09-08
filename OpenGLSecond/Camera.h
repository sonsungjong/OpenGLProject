#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "Shader.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera
{
protected:
	glm::vec3 Position;
	glm::vec3 Orientation;
	glm::vec3 Up;
	glm::mat4 cameraMatrix;

	int width;
	int height;

	float speed;
	float sensitivity;
	bool firstClick;

public:
	Camera(int width, int height, glm::vec3 position);

	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);

	glm::vec3 GetPosition();
};

#endif