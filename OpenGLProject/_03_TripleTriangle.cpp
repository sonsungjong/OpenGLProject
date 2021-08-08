#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

// Vertex Shader �ҽ��ڵ�
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment Shader �ҽ��ڵ�
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"		FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	// �ʱ�ȭ
	glfwInit();

	// �������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile ���
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLfloat vertices[] =
	//{
	//	-0.5f, -0.5f*float(sqrt(3))/3, 0.0f,			// �ϴ� ����
	//	0.5f, -0.5f*float(sqrt(3))/3, 0.0f,				// �ϴ� ����
	//	0.0f, 0.5f*float(sqrt(3))*2/3, 0.0f,			// ���
	//	-0.5f/2, 0.5f*float(sqrt(3))/6, 0.0f,			// ���� ����
	//	0.5f/2, 0.5f*float(sqrt(3))/6, 0.0f,			// ���� ����
	//	0.0f, -0.5f*float(sqrt(3))/3, 0.0f,				// ���� �ϴ�
	//};

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,			// �ϴ� ����
		0.5f, -0.5f, 0.0f,				// �ϴ� ����
		0.0f, 0.5f, 0.0f,			// ���
		-0.25f, 0.0f, 0.0f,			// ���� ����
		0.25f, 0.0f, 0.0f,			// ���� ����
		0.0f, -0.5f, 0.0f,				// ���� �ϴ�
	};

	// vertices ���� ������ �� ��Ʈ����
	GLuint indices[] =
	{
		0, 3, 5,			// �ϴ� ���� �ﰢ�� ��ǥ (vertices�� 0��, 3,�� 5��)
		3, 2, 4,			// ��� �ﰢ�� (vertices�� 3��, 2��, 4��)
		5, 4, 1,			// �ϴ� ���� �ﰢ�� (vertices�� 5��, 4��, 1��)
	};

	// GLFWwindow ����
	GLFWwindow* window = glfwCreateWindow(800, 800, "SungJong03", NULL, NULL);

	if (window == NULL) {		// window �������� üũ
		cout << "GLFW window ���� ����" << endl;
		glfwTerminate();
		return -1;
	}

	// ���� context �ȿ� window ��ü ����
	glfwMakeContextCurrent(window);

	// Load GLAD
	gladLoadGL();
	// viewport ũ�� ����
	glViewport(0, 0, 800, 800);

	// Vertex Shader Object�� �� ���۷����� �����Ѵ�
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Vertex Shader Object�� Vertex Shader�ҽ��ڵ带 ���δ�
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Vertex Shader�� ������
	glCompileShader(vertexShader);

	// Fragment Shader Object�� �� ���۷����� �����Ѵ�
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Fragment Shader�ҽ��ڵ带 Fragment Shader Object�� ���δ�
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// ���̴��� �������Ѵ�
	glCompileShader(fragmentShader);

	// Shader Program Object �� �� ���۷����� �����Ѵ�
	GLuint shaderProgram = glCreateProgram();
	// Vertex ���̴��� Fragment ���̴��� Shader Program�� ���δ�
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// shaderProgram�� Link
	glLinkProgram(shaderProgram);

	// ��������ʴ� Vertex�� Fragment ���̴� ��ü�� �����Ѵ�.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Vertex Array Object, Vertex Buffer Object ���۷��� �����̳� ����
	GLuint VAO, VBO, EBO;

	// VAO, VBO, EBO�� �� 1���� ����
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// ���� Vertex Array Object�� ���� VAO�� �����.
	glBindVertexArray(VAO);

	// Buffer ���ε� �� vertices �����͸� ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Buffer�� Vertex �Ӽ��� ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// �߸� �����ϴ� ���� �����ϱ� ���� 0���� ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// ��׶��� ����
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// back ���� Ŭ�� �� �� ���� �Ҵ�
		glClear(GL_COLOR_BUFFER_BIT);
		// ����� shader ���
		glUseProgram(shaderProgram);
		// VAO ���ε�
		glBindVertexArray(VAO);
		// GL_TRIANGLES�� ����� �ﰢ�� �׸���
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// back���ۿ� front���� ��ü
		glfwSwapBuffers(window);

		// ��� GLFW �̺�Ʈ ó��
		glfwPollEvents();
	}

	// object ����
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	
	// ���α׷� ���� �� window�� GLFW ����
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
