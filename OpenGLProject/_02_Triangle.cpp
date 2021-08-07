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

int main()
{
	// �ʱ�ȭ
	glfwInit();

	// �������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// CORE profile ���
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// OpenGL ���� float
	// shader�� OpenGL object.
	// �ﰢ�� ��ǥ
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,			// �ϴ� ����
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,				// �ϴ� ����
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f			// ���
	};

	// GLFWwindow��ü ����
	GLFWwindow* window = glfwCreateWindow(800, 800, "SungJong02", NULL, NULL);

	// window �������� üũ
	if (window == NULL)
	{
		cout << "GLFW window ���� ����" << endl;
		glfwTerminate();
		return -1;
	}

	// ���� context�ȿ� window�� ����
	glfwMakeContextCurrent(window);

	// Load GLAD
	gladLoadGL();
	// Viewport ���
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


	// Vertex Array Object, Vertex Buffer Object
	GLuint VAO, VBO;

	// ���� 1�� �����Ѵ�.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// ���� VAO�� ���� Vertex Array Object�� �����.
	glBindVertexArray(VAO);

	// ���� VBO�� GL_ARRAY_BUFFER�� ���´�.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// VBO�ȿ� vertices�� �ִ´�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// OpenGL�� ��� VBO�� ������ ���ϱ� ���� Vertex �Ӽ��� �����Ѵ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	// OpenGL�� �װ��� ����� �� �ֵ��� Vertex �Ӽ��� ����Ѵ�.
	glEnableVertexAttribArray(0);

	// �߸� �����ϴ� ���� �����ϱ� ���� VBO�� VAO�� 0���� ���´�.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ��׶��� ���� ���
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// back���� ���ſ� ���ο� ���� �Ҵ�
	glClear(GL_COLOR_BUFFER_BIT);
	// back���ۿ� front���� ��ü
	glfwSwapBuffers(window);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Shader Program ���
		glUseProgram(shaderProgram);
		// ����� VAO�� ���´�.
		glBindVertexArray(VAO);
		// GL_TRIANGLES�� �ﰢ���� �׸���
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		// ��� GLFW �̺�Ʈ�� ó���ϴ� �Լ�
		glfwPollEvents();
	}

	// ��� ��ü�� ����
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// ���α׷� ���� ���� windowâ�� ���ش�.
	glfwDestroyWindow(window);
	// ���α׷� ���� ���� GLFW�� �����Ѵ�.
	glfwTerminate();

	return 0;
}