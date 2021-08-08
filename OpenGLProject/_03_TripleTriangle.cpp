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

int main() {
	// 초기화
	glfwInit();

	// 버전명시
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile 명시
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLfloat vertices[] =
	//{
	//	-0.5f, -0.5f*float(sqrt(3))/3, 0.0f,			// 하단 좌측
	//	0.5f, -0.5f*float(sqrt(3))/3, 0.0f,				// 하단 우측
	//	0.0f, 0.5f*float(sqrt(3))*2/3, 0.0f,			// 상단
	//	-0.5f/2, 0.5f*float(sqrt(3))/6, 0.0f,			// 내부 좌측
	//	0.5f/2, 0.5f*float(sqrt(3))/6, 0.0f,			// 내부 우측
	//	0.0f, -0.5f*float(sqrt(3))/3, 0.0f,				// 내부 하단
	//};

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,			// 하단 좌측
		0.5f, -0.5f, 0.0f,				// 하단 우측
		0.0f, 0.5f, 0.0f,			// 상단
		-0.25f, 0.0f, 0.0f,			// 내부 좌측
		0.25f, 0.0f, 0.0f,			// 내부 우측
		0.0f, -0.5f, 0.0f,				// 내부 하단
	};

	// vertices 점을 가져다 쓸 매트릭스
	GLuint indices[] =
	{
		0, 3, 5,			// 하단 좌측 삼각형 좌표 (vertices의 0행, 3,행 5행)
		3, 2, 4,			// 상단 삼각형 (vertices의 3행, 2행, 4행)
		5, 4, 1,			// 하단 우측 삼각형 (vertices의 5행, 4행, 1행)
	};

	// GLFWwindow 생성
	GLFWwindow* window = glfwCreateWindow(800, 800, "SungJong03", NULL, NULL);

	if (window == NULL) {		// window 생성실패 체크
		cout << "GLFW window 생성 실패" << endl;
		glfwTerminate();
		return -1;
	}

	// 현재 context 안에 window 객체 도입
	glfwMakeContextCurrent(window);

	// Load GLAD
	gladLoadGL();
	// viewport 크기 지정
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

	// Vertex Array Object, Vertex Buffer Object 레퍼런스 컨테이너 생성
	GLuint VAO, VBO, EBO;

	// VAO, VBO, EBO를 각 1개씩 생성
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 현재 Vertex Array Object를 변수 VAO로 만든다.
	glBindVertexArray(VAO);

	// Buffer 바인딩 후 vertices 데이터를 도입
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// Buffer의 Vertex 속성을 지정
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 잘못 수정하는 것을 방지하기 위해 0으로 묶음
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// 백그라운드 색상
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// back 버퍼 클린 후 새 색상 할당
		glClear(GL_COLOR_BUFFER_BIT);
		// 사용할 shader 명시
		glUseProgram(shaderProgram);
		// VAO 바인딩
		glBindVertexArray(VAO);
		// GL_TRIANGLES를 사용해 삼각형 그리기
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// back버퍼와 front버퍼 교체
		glfwSwapBuffers(window);

		// 모든 GLFW 이벤트 처리
		glfwPollEvents();
	}

	// object 해제
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	
	// 프로그램 종료 전 window와 GLFW 해제
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
