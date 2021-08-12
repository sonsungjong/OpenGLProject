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
	// Core Profile 명시
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// mac os 호환성
# ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COPMPAT, GL_TRUE)
#endif

		// GLFWwindow 포인터자료형으로 window 객체 생성, 크기와 제목지정
		GLFWwindow* window = glfwCreateWindow(800, 600, "SonSungJong07", NULL, NULL);
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

	// 예외 체크
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "vertex shader 오류 발생 : " << infoLog << endl;
	}

	// compile fragment shader1
	unsigned int fragmentShaders[2];

	fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
	string fragShaderSrc = loadShaderSrc("fragment_core.glsl");
	const GLchar* fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShaders[0], 1, &fragShader, NULL);
	glCompileShader(fragmentShaders[0]);

	// 오류 체크1
	glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infoLog);
		cout << "frag shader 오류 발생 : " << infoLog << endl;
	}

	//2
	fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
	fragShaderSrc = loadShaderSrc("fragment_core2.glsl");
	fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShaders[1], 1, &fragShader, NULL);
	glCompileShader(fragmentShaders[1]);

	// 오류 체크2
	glGetShaderiv(fragmentShaders[1], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infoLog);
		cout << "frag shader 오류 발생 : " << infoLog << endl;
	}

	unsigned int shaderPrograms[2];
	shaderPrograms[0] = glCreateProgram();

	glAttachShader(shaderPrograms[0], vertexShader);
	glAttachShader(shaderPrograms[0], fragmentShaders[0]);
	glLinkProgram(shaderPrograms[0]);

	// 오류 체크
	glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infoLog);
		cout << "링크 오류 : " << infoLog << endl;
	}

	shaderPrograms[1] = glCreateProgram();

	glAttachShader(shaderPrograms[1], vertexShader);
	glAttachShader(shaderPrograms[1], fragmentShaders[1]);
	glLinkProgram(shaderPrograms[1]);

	// 오류 체크
	glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infoLog);
		cout << "링크 오류 : " << infoLog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaders[0]);
	glDeleteShader(fragmentShaders[1]);

	// 정점 좌표 배열
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

		0.5f, 0.5f, 0.0f,			// 우측 상단
		-0.5f, 0.5f, 0.0f,			// 좌측 상단
		-0.5f, -0.5f, 0.0f,		// 좌측 하단
		0.5f, -0.5f, 0.0f			// 우측 하단
	};

	// vertices의 좌표를 이용
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

	// 점 속성 셋팅
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

	// glfw 해제
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
		cout << "열기 실패" << filename << endl;
	}

	file.close();

	return ret;
}