#include "Shader.h"
using namespace std;

int main05() {
	cout << "Hello OpenGL" << endl;
	// 1. �ʱ�ȭ
	glfwInit();
	// 2. ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.8f, 0.3f, 0.02f,				// �ϴ� ����
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,			0.8f, 0.3f, 0.02f,				// �ϴ� ����
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,		1.0f, 0.6f, 0.32f,				// ���
		-0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f,		0.9f, 0.45f, 0.17f,			// ���� ����
		0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f,			0.9f, 0.45f, 0.17f,			// ���� ����
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,			0.8f, 0.3f, 0.02f				// ���� �ϴ�
	};

	GLuint indices[] =
	{
		0, 3, 5,			// �ϴ� ���� �ﰢ�� ��ǥ (vertices�� 0��, 3,�� 5��)
		3, 2, 4,			// ��� �ﰢ�� (vertices�� 3��, 2��, 4��)
		5, 4, 1,			// �ϴ� ���� �ﰢ�� (vertices�� 5��, 4��, 1��)
	};

	// 3. window����
	GLFWwindow* window = glfwCreateWindow(800, 800, "Caption05", NULL, NULL);
	if (window == NULL) {
		cout << "window���� ����" << endl;
		glfwTerminate();
		return -1;
	}
	// 4. ����Context����� View����
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("vertex.glsl", "frag.glsl");

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ��ǥ ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ���� ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// �߸� �����ϴ� ���� �����ϱ� ���� 0���� ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	shaderProgram.Rotation();

	// 6. Main loop
	while (!glfwWindowShouldClose(window)) {
		// ����
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.RotationRepeat();

		// TODO: ���⿡ �ڵ��ۼ�
		shaderProgram.Activate();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// ��� �̺�Ʈ ó��
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	shaderProgram.Delete();

	// 9. ����
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}