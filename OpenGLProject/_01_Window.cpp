#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

int main01() {

	// GLFW �ʱ�ȭ
	glfwInit();

	// ����ϴ� OpenGL ���� �˷��ֱ�
	// ������ 3.3ver ��� ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// CORE profile ��� ���̶�� GLFW�� �˷��ֱ�
	// -> modern functions�� ��� ����
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFWwindow ��ü�� 800 x 800 pixels�� ����������ϰ�, �̸��� �����ش�
	GLFWwindow* window = glfwCreateWindow(800, 800, "SungJong01", NULL, NULL);
	// ������ ������ �����ϴ� ������ üũ
	if (window == NULL) {
		cout << "GLFW window ������ �����Ͽ����ϴ�." << endl;
		glfwTerminate();
		return -1;
	}
	// ���� context�ȿ� window�� ����
	glfwMakeContextCurrent(window);

	// GLAD�� Load
	gladLoadGL();

	// window�� OpenGL�� viewport�� ����Ѵ�
	// viewport : x=0, y=0 to x=800, y=800
	glViewport(0, 0, 800, 800);

	// ���� ���
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// back�� ���۸� �����ϰ� ���ο� ������ �Ҵ��Ѵ�.
	glClear(GL_COLOR_BUFFER_BIT);
	// front�� ���ۿ� ���� ��ü�Ѵ�.
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// ��� GLFW �̺�Ʈ�� ó���ϴ� �Լ�
		glfwPollEvents();
	}

	// ���α׷� ���� ���� windowâ�� ���ش�.
	glfwDestroyWindow(window);
	// ���α׷� ���� ���� GLFW�� �����Ѵ�.
	glfwTerminate();

	return 0;
}