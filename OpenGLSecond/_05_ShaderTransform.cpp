#include "Shader.h"
using namespace std;

int main() {
	cout << "Hello OpenGL" << endl;
	// 1. 초기화
	glfwInit();
	// 2. 버전
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.8f, 0.3f, 0.02f,				// 하단 좌측
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,			0.8f, 0.3f, 0.02f,				// 하단 우측
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,		1.0f, 0.6f, 0.32f,				// 상단
		-0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f,		0.9f, 0.45f, 0.17f,			// 내부 좌측
		0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f,			0.9f, 0.45f, 0.17f,			// 내부 우측
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,			0.8f, 0.3f, 0.02f				// 내부 하단
	};

	GLuint indices[] =
	{
		0, 3, 5,			// 하단 좌측 삼각형 좌표 (vertices의 0행, 3,행 5행)
		3, 2, 4,			// 상단 삼각형 (vertices의 3행, 2행, 4행)
		5, 4, 1,			// 하단 우측 삼각형 (vertices의 5행, 4행, 1행)
	};

	// 3. window생성
	GLFWwindow* window = glfwCreateWindow(800, 800, "Caption05", NULL, NULL);
	if (window == NULL) {
		cout << "window생성 실패" << endl;
		glfwTerminate();
		return -1;
	}
	// 4. 현재Context만들어 View띄우기
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

	// 좌표 적용
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 색상 적용
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// 잘못 수정하는 것을 방지하기 위해 0으로 묶음
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	shaderProgram.Rotation();

	// 6. Main loop
	while (!glfwWindowShouldClose(window)) {
		// 배경색
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.RotationRepeat();

		// TODO: 여기에 코드작성
		shaderProgram.Activate();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// 모든 이벤트 처리
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	shaderProgram.Delete();

	// 9. 해제
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}