#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
string loadShaderSrc(const char* filename);

int main07() {
	int success;
	char infoLog[512];

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile ���
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// mac os ȣȯ��
# ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COPMPAT, GL_TRUE)
#endif

		// GLFWwindow �������ڷ������� window ��ü ����, ũ��� ��������
		GLFWwindow* window = glfwCreateWindow(800, 600, "SonSungJong07", NULL, NULL);
	if (window == NULL) {		// �����찡 �������� ����
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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*
		shaders
	*/

	// compile vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	string vertShaderSrc = loadShaderSrc("vertex_core.glsl");

	const GLchar* vertShader = vertShaderSrc.c_str();
	glShaderSource(vertexShader, 1, &vertShader, NULL);
	glCompileShader(vertexShader);

	// ���� üũ
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "vertex shader ���� �߻� : " << infoLog << endl;
	}

	// compile fragment shader1
	unsigned int fragmentShaders[2];

	fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
	string fragShaderSrc = loadShaderSrc("fragment_core.glsl");
	const GLchar* fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShaders[0], 1, &fragShader, NULL);
	glCompileShader(fragmentShaders[0]);

	// ���� üũ1
	glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infoLog);
		cout << "frag shader ���� �߻� : " << infoLog << endl;
	}

	//2
	fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
	fragShaderSrc = loadShaderSrc("fragment_core2.glsl");
	fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShaders[1], 1, &fragShader, NULL);
	glCompileShader(fragmentShaders[1]);

	// ���� üũ2
	glGetShaderiv(fragmentShaders[1], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infoLog);
		cout << "frag shader ���� �߻� : " << infoLog << endl;
	}

	unsigned int shaderPrograms[2];
	shaderPrograms[0] = glCreateProgram();

	glAttachShader(shaderPrograms[0], vertexShader);
	glAttachShader(shaderPrograms[0], fragmentShaders[0]);
	glLinkProgram(shaderPrograms[0]);

	// ���� üũ
	glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infoLog);
		cout << "��ũ ���� : " << infoLog << endl;
	}

	shaderPrograms[1] = glCreateProgram();

	glAttachShader(shaderPrograms[1], vertexShader);
	glAttachShader(shaderPrograms[1], fragmentShaders[1]);
	glLinkProgram(shaderPrograms[1]);

	// ���� üũ
	glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infoLog);
		cout << "��ũ ���� : " << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaders[0]);
	glDeleteShader(fragmentShaders[1]);

	// ���� ��ǥ �迭
	float vertices[] = {
		// triangle
		/*-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f*/

		/*
		// first triangle
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		// second triangle
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
		*/

		0.5f, 0.5f, 0.0f,			// ���� ���
		-0.5f, 0.5f, 0.0f,			// ���� ���
		-0.5f, -0.5f, 0.0f,		// ���� �ϴ�
		0.5f, -0.5f, 0.0f			// ���� �ϴ�
	};

	// vertices�� ��ǥ�� �̿�
	unsigned int indices[] = 
	{
		0, 1, 2,			// first triangle
		2, 3, 0			// second triangle
	};

	// VAO, VBO
	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind VAO, VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// �� �Ӽ� ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// 2. process input
		processInput(window);

		// 3. render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 4. draw shapes
		glBindVertexArray(VAO);
		glUseProgram(shaderPrograms[0]);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glUseProgram(shaderPrograms[1]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3*sizeof(unsigned int)));

		// 1. send new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw ����
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

string loadShaderSrc(const char* filename) {
	ifstream file;
	stringstream buf;

	string ret = "";

	file.open(filename);

	if (file.is_open()) {
		buf << file.rdbuf();
		ret = buf.str();
	}
	else {
		cout << "���� ����" << filename << endl;
	}

	file.close();

	return ret;
}