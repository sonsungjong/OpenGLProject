#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

void framebuffer_size_callback08(GLFWwindow* window, int width, int height);
void processInput08(GLFWwindow* window);
string loadShaderSrc08(const char* filename);

int main08() {
	int success;
	char infoLog[512];

	// 초기화
	glfwInit();
	// version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "SungJong08", NULL, NULL);
	if (window == NULL) { // window not created
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
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback08);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	string vertShaderSrc = loadShaderSrc08("_08_vertex.glsl");
	const GLchar* vertShader = vertShaderSrc.c_str();
	glShaderSource(vertexShader, 1, &vertShader, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "vertex shader 에러" << endl << infoLog << endl;
	}

	unsigned int fragmentShaders[2];

	fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
	string fragShaderSrc = loadShaderSrc08("_08_fragment.glsl");
	const GLchar* fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShaders[0], 1, &fragShader, NULL);
	glCompileShader(fragmentShaders[0]);

	glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaders[0], 512, NULL, infoLog);
		cout << "fragment shader 오류" << endl << infoLog << endl;
	}

	/*fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
	fragShaderSrc = loadShaderSrc08("_08_fragment2.glsl");
	fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShaders[1], 1, &fragShader, NULL);
	glCompileShader(fragmentShaders[1]);

	glGetShaderiv(fragmentShaders[1], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaders[1], 512, NULL, infoLog);
		cout << "fragment shader2 오류" << endl << infoLog << endl;
	}*/

	// 쉐이더 프로그램
	unsigned int shaderPrograms[2];

	shaderPrograms[0] = glCreateProgram();

	glAttachShader(shaderPrograms[0], vertexShader);
	glAttachShader(shaderPrograms[0], fragmentShaders[0]);
	glLinkProgram(shaderPrograms[0]);

	glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderPrograms[0], 512, NULL, infoLog);
		cout << "연결 오류" << endl << infoLog << endl;
	}

	/*shaderPrograms[1] = glCreateProgram();

	glAttachShader(shaderPrograms[1], vertexShader);
	glAttachShader(shaderPrograms[1], fragmentShaders[1]);
	glLinkProgram(shaderPrograms[1]);

	glGetProgramiv(shaderPrograms[1], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderPrograms[1], 512, NULL, infoLog);
		cout << "연결 오류2" << endl << infoLog << endl;
	}*/

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaders[0]);
	//glDeleteShader(fragmentShaders[1]);

	// 좌표
	float vertices[] = {
		// Position									Color
		-0.25f, -0.5f, 0.0f,			1.0f, 1.0f, 0.5f,
		0.15f, 0.0f, 0.0f,				0.5f, 1.0f, 0.75f,
		0.0f, 0.5f, 0.0f,				0.6f, 1.0f, 0.2f,
		0.5f, -0.4f, 0.0f,				1.0f, 0.2f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,			// 삼각형1
		3, 1, 2				// 삼각형2
	};

	// generate VAO, VBO, EBO
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 좌표 적용
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 색상 적용
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// 회전
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glUseProgram(shaderPrograms[0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(trans));

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// 2. process input
		processInput08(window);

		// 3. render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 회전
		trans = glm::rotate(trans, glm::radians((float)glfwGetTime()/ 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[0], "transform"), 1, GL_FALSE, glm::value_ptr(trans));

		// 4. draw shapes
		glBindVertexArray(VAO);
		// 삼각형1
		glUseProgram(shaderPrograms[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//삼각형2
		//glUseProgram(shaderPrograms[1]);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));
		glBindVertexArray(0);

		// 1. send new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw 해제
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback08(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput08(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

string loadShaderSrc08(const char* filename) {
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