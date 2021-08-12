#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void framebuffer_size_callback1(GLFWwindow* window, int width, int height);

int main02() {
	cout << "Hello, world!" << endl;

	// glm test : https://github.com/g-truc/glm/releases
	glm::vec4 vec(1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);			// indentity matrix
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));			// translation
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));			// rotation
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));			// scaling
	vec = trans * vec;
	cout << vec.x << '\t' << vec.y << '\t' << vec.z << endl;

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile 명시
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// mac os 호환성
# ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COPMPAT, GL_TRUE)
#endif
	// GLFWwindow 포인터자료형으로 window 객체 생성, 크기와 제목지정
	GLFWwindow* window = glfwCreateWindow(800, 600, "SonSungJong02", NULL, NULL);

	if (window == NULL) {		// 윈도우가 생성되지 않음
		cout << "Could not create window." << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		return -1;
	}
	// 0,0 to 800,800
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback1);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// 2. process input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		// 3. render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 1. send new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw 해제
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback1(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
