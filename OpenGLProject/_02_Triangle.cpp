#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

// Vertex Shader 소스코드
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment Shader 소스코드
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"		FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	// 초기화
	glfwInit();

	// 버전명시
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// CORE profile 명시
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// OpenGL 전용 float
	// shader란 OpenGL object.
	// 삼각형 좌표
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,			// 하단 좌측
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,				// 하단 우측
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f			// 상단
	};

	// GLFWwindow객체 생성
	GLFWwindow* window = glfwCreateWindow(800, 800, "SungJong02", NULL, NULL);

	// window 생성실패 체크
	if (window == NULL)
	{
		cout << "GLFW window 생성 실패" << endl;
		glfwTerminate();
		return -1;
	}

	// 현재 context안에 window를 도입
	glfwMakeContextCurrent(window);

	// Load GLAD
	gladLoadGL();
	// Viewport 명시
	glViewport(0, 0, 800, 800);

	// Vertex Shader Object와 그 레퍼런스를 생성한다
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Vertex Shader Object에 Vertex Shader소스코드를 붙인다
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Vertex Shader를 컴파일
	glCompileShader(vertexShader);

	// Fragment Shader Object와 그 레퍼런스를 생성한다
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Fragment Shader소스코드를 Fragment Shader Object에 붙인다
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// 쉐이더를 컴파일한다
	glCompileShader(fragmentShader);

	// Shader Program Object 와 그 레퍼런스를 생성한다
	GLuint shaderProgram = glCreateProgram();
	// Vertex 쉐이더와 Fragment 쉐이더를 Shader Program에 붙인다
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// shaderProgram을 Link
	glLinkProgram(shaderProgram);

	// 사용하지않는 Vertex와 Fragment 쉐이더 객체를 해제한다.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Vertex Array Object, Vertex Buffer Object
	GLuint VAO, VBO;

	// 각각 1씩 생성한다.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// 변수 VAO를 현재 Vertex Array Object로 만든다.
	glBindVertexArray(VAO);

	// 변수 VBO를 GL_ARRAY_BUFFER로 묶는다.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// VBO안에 vertices를 넣는다.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// OpenGL이 어떻게 VBO를 읽을지 정하기 위해 Vertex 속성을 구성한다
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	// OpenGL이 그것을 사용할 수 있도록 Vertex 속성을 허용한다.
	glEnableVertexAttribArray(0);

	// 잘못 수정하는 것을 방지하기 위해 VBO와 VAO를 0으로 묶는다.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 백그라운드 색상 명시
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// back버퍼 제거와 새로운 색상 할당
	glClear(GL_COLOR_BUFFER_BIT);
	// back버퍼와 front버퍼 교체
	glfwSwapBuffers(window);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Shader Program 사용
		glUseProgram(shaderProgram);
		// 사용할 VAO를 묶는다.
		glBindVertexArray(VAO);
		// GL_TRIANGLES로 삼각형을 그린다
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		// 모든 GLFW 이벤트를 처리하는 함수
		glfwPollEvents();
	}

	// 모든 객체를 해제
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// 프로그램 종료 전에 window창을 없앤다.
	glfwDestroyWindow(window);
	// 프로그램 종료 전에 GLFW를 제거한다.
	glfwTerminate();

	return 0;
}