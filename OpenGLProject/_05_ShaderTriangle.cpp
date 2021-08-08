#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "EBO.h"

using namespace std;

int main05() {
	// 초기화
	glfwInit();

	// 버전명시
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile 명시
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 좌표(x,y,z)와 색상
	GLfloat vertices[] =
	{
		-0.5f, -0.5f*float(sqrt(3))/3, 0.0f,		0.8f, 0.3f, 0.02f,				// 하단 좌측
		0.5f, -0.5f*float(sqrt(3))/3, 0.0f,			0.8f, 0.3f, 0.02f,				// 하단 우측
		0.0f, 0.5f*float(sqrt(3))*2/3, 0.0f,		1.0f, 0.6f, 0.32f,				// 상단
		-0.25f, 0.5f*float(sqrt(3))/6, 0.0f,		0.9f, 0.45f, 0.17f,			// 내부 좌측
		0.25f, 0.5f*float(sqrt(3))/6, 0.0f,			0.9f, 0.45f, 0.17f,			// 내부 우측
		0.0f, -0.5f*float(sqrt(3))/3, 0.0f,			0.8f, 0.3f, 0.02f				// 내부 하단
	};

	// vertices 점을 가져다 쓸 매트릭스
	GLuint indices[] =
	{
		0, 3, 5,			// 하단 좌측 삼각형 좌표 (vertices의 0행, 3,행 5행)
		3, 2, 4,			// 상단 삼각형 (vertices의 3행, 2행, 4행)
		5, 4, 1,			// 하단 우측 삼각형 (vertices의 5행, 4행, 1행)
	};

	// GLFWwindow 생성
	GLFWwindow* window = glfwCreateWindow(800, 800, "SungJong05", NULL, NULL);

	if (window == NULL) {		// window 생성실패 체크
		cout << "GLFW window 생성 실패" << endl;
		glfwTerminate();
		return -1;
	}

	// 현재 context 안에 window 객체 도입
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// Shader 객체를 생성한다. (text파일 사용)
	shaderClass shaderProgram("default2.vert", "default2.frag");

	// Vertex Array Object를 생성 후 바인드한다.
	VAO VAO1;
	VAO1.Bind();

	// Vertex Buffer Object 와 Element Buffer Object를 생성하고 각 변수와 연결한다
	VBO VBO1(vertices, sizeof(vertices));			// vertices
	EBO EBO1(indices, sizeof(indices));				// indices

	// VAO에 VBO를 링크
	//VAO1.LinkVBO(VBO1, 0);
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
	// 수정을 막기 위해 바인드 해제
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// 백그라운드 색상
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// back 버퍼 클린 후 새 색상 할당
		glClear(GL_COLOR_BUFFER_BIT);
		// 사용할 shader 명시
		shaderProgram.Activate();
		// VAO 바인딩
		VAO1.Bind();
		// GL_TRIANGLES를 사용해 삼각형 그리기
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// back버퍼와 front버퍼 교체
		glfwSwapBuffers(window);

		// 모든 GLFW 이벤트 처리
		glfwPollEvents();
	}

	// object 해제
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// 프로그램 종료 전 window와 GLFW 해제
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}