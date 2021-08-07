#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

int main01() {

	// GLFW 초기화
	glfwInit();

	// 사용하는 OpenGL 버전 알려주기
	// 지금은 3.3ver 사용 중
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// CORE profile 사용 중이라고 GLFW에 알려주기
	// -> modern functions만 사용 가능
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFWwindow 객체가 800 x 800 pixels로 만들어지게하고, 이름을 정해준다
	GLFWwindow* window = glfwCreateWindow(800, 800, "SungJong01", NULL, NULL);
	// 윈도우 생성에 실패하는 에러를 체크
	if (window == NULL) {
		cout << "GLFW window 생성에 실패하였습니다." << endl;
		glfwTerminate();
		return -1;
	}
	// 현재 context안에 window를 도입
	glfwMakeContextCurrent(window);

	// GLAD를 Load
	gladLoadGL();

	// window속 OpenGL의 viewport를 명시한다
	// viewport : x=0, y=0 to x=800, y=800
	glViewport(0, 0, 800, 800);

	// 배경색 명시
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// back단 버퍼를 해제하고 새로운 색깔을 할당한다.
	glClear(GL_COLOR_BUFFER_BIT);
	// front단 버퍼와 색을 교체한다.
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// 모든 GLFW 이벤트를 처리하는 함수
		glfwPollEvents();
	}

	// 프로그램 종료 전에 window창을 없앤다.
	glfwDestroyWindow(window);
	// 프로그램 종료 전에 GLFW를 제거한다.
	glfwTerminate();

	return 0;
}