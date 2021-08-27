#include "Shader.h"

using namespace std;

int main04() {
	cout << "OpenGL 실행" << endl;
	// 점좌표
	GLfloat vertices[] = {
		-0.25f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
		-0.5f, 0.0f, 0.0f,			0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,			0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.0f,			1.0f, 1.0f, 1.0f,
		0.25f, -0.5f, 0.0f,			1.0f, 1.0f, 1.0f
	};
	// 선
	GLuint indices[] = {
		0, 1, 2,
		0, 2, 4,
		2, 3, 4
	};
	// 1. 초기화
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// 2. window생성
	GLFWwindow* window = glfwCreateWindow(800, 800, "Caption04", NULL, NULL);
	if (window == NULL) {
		cout << "window 생성 실패" << endl;
		glfwTerminate();
		return -1;
	}
	// 3. View화면만들기
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	// 4. 쉐이더 불러오기
	Shader shaderProgram("_04_vertex.glsl", "_04_frag.glsl");
	// 5. Vertex 지정
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// 잘못 수정하는 것을 방지하기 위해 0으로 묶음
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// 6. Main loop
	while (!glfwWindowShouldClose(window)) {
		// 배경색
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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