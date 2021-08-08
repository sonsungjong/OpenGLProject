#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "EBO.h"

using namespace std;

int main05() {
	// �ʱ�ȭ
	glfwInit();

	// �������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile ���
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��ǥ(x,y,z)�� ����
	GLfloat vertices[] =
	{
		-0.5f, -0.5f*float(sqrt(3))/3, 0.0f,		0.8f, 0.3f, 0.02f,				// �ϴ� ����
		0.5f, -0.5f*float(sqrt(3))/3, 0.0f,			0.8f, 0.3f, 0.02f,				// �ϴ� ����
		0.0f, 0.5f*float(sqrt(3))*2/3, 0.0f,		1.0f, 0.6f, 0.32f,				// ���
		-0.25f, 0.5f*float(sqrt(3))/6, 0.0f,		0.9f, 0.45f, 0.17f,			// ���� ����
		0.25f, 0.5f*float(sqrt(3))/6, 0.0f,			0.9f, 0.45f, 0.17f,			// ���� ����
		0.0f, -0.5f*float(sqrt(3))/3, 0.0f,			0.8f, 0.3f, 0.02f				// ���� �ϴ�
	};

	// vertices ���� ������ �� ��Ʈ����
	GLuint indices[] =
	{
		0, 3, 5,			// �ϴ� ���� �ﰢ�� ��ǥ (vertices�� 0��, 3,�� 5��)
		3, 2, 4,			// ��� �ﰢ�� (vertices�� 3��, 2��, 4��)
		5, 4, 1,			// �ϴ� ���� �ﰢ�� (vertices�� 5��, 4��, 1��)
	};

	// GLFWwindow ����
	GLFWwindow* window = glfwCreateWindow(800, 800, "SungJong05", NULL, NULL);

	if (window == NULL) {		// window �������� üũ
		cout << "GLFW window ���� ����" << endl;
		glfwTerminate();
		return -1;
	}

	// ���� context �ȿ� window ��ü ����
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// Shader ��ü�� �����Ѵ�. (text���� ���)
	shaderClass shaderProgram("default2.vert", "default2.frag");

	// Vertex Array Object�� ���� �� ���ε��Ѵ�.
	VAO VAO1;
	VAO1.Bind();

	// Vertex Buffer Object �� Element Buffer Object�� �����ϰ� �� ������ �����Ѵ�
	VBO VBO1(vertices, sizeof(vertices));			// vertices
	EBO EBO1(indices, sizeof(indices));				// indices

	// VAO�� VBO�� ��ũ
	//VAO1.LinkVBO(VBO1, 0);
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
	// ������ ���� ���� ���ε� ����
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// ��׶��� ����
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// back ���� Ŭ�� �� �� ���� �Ҵ�
		glClear(GL_COLOR_BUFFER_BIT);
		// ����� shader ���
		shaderProgram.Activate();
		// VAO ���ε�
		VAO1.Bind();
		// GL_TRIANGLES�� ����� �ﰢ�� �׸���
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// back���ۿ� front���� ��ü
		glfwSwapBuffers(window);

		// ��� GLFW �̺�Ʈ ó��
		glfwPollEvents();
	}

	// object ����
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// ���α׷� ���� �� window�� GLFW ����
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}