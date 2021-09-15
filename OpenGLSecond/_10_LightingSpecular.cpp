#include "Camera.h"

using namespace std;

int main()
{
	unsigned int width = 800;
	unsigned int height = 800;

	GLfloat vertices[] =
	{
		// coordinates, color, texCoord, normals
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, // Bottom side
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, 1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,		5.0f, 5.0f,      0.0f, 1.0f, 0.0f,
		0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,		5.0f, 0.0f,      0.0f, 1.0f, 0.0f

		//-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Top side
		//-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f,
		//0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,		5.0f, 5.0f,      0.0f, -1.0f, 0.0f,
		//0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,		5.0f, 0.0f,      0.0f, -1.0f, 0.0f,

		//-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
		//-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f,
		// 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,		2.5f, 5.0f,     -0.8f, 0.5f,  0.0f,

		//-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
		// 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f,      0.0f, 0.5f, -0.8f,
		// 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,		2.5f, 5.0f,      0.0f, 0.5f, -0.8f,

		// 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,		0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
		// 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,		5.0f, 0.0f,      0.8f, 0.5f,  0.0f,
		// 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,		2.5f, 5.0f,      0.8f, 0.5f,  0.0f,

		// 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,		5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
		//-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f,
		// 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,		2.5f, 5.0f,      0.0f, 0.5f,  0.8f
	};

	GLuint indices[] =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		//4, 5, 6,
		//4, 6, 7
	};

	GLfloat lightVertices[] =
	{
		-0.1f, -0.1f, 0.1f,
		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, 0.1f,
		-0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, 0.1f,
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Lighting10", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader pyramidShader("pyramid.vert", "pyramid.frag");
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Shader lightShader("lighting.vert", "lighting.frag");
	GLuint lightVAO, lightVBO, lightEBO;
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glGenBuffers(1, &lightEBO);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	pyramidShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(pyramidShader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(pyramidShader.GetID(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(pyramidShader.GetID(), "lightPos"), lightColor.x, lightColor.y, lightColor.z);

	// texture
	GLuint texture;
	int imgWidth, imgHeight, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("brick.png", &imgWidth, &imgHeight, &numColCh, 0);

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(pyramidShader.GetID(), "tex0");
	pyramidShader.Activate();
	glUniform1i(tex0Uni, 0);

	// Depth Buffer 사용
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		pyramidShader.Activate();
		// 스펙큘러 라이팅을 위해 카메라 위치를 Fragment Shader로 보냄
		glUniform3f(glGetUniformLocation(pyramidShader.GetID(), "camPos"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// camMatrix를 light의 Vertex Shader로 보냄
		camera.Matrix(pyramidShader, "camMatrix");
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		// 그린다 primitives, indices의 수, indices의 데이터타입, indices의 위치
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		glBindVertexArray(lightVAO);
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture);
	pyramidShader.Delete();

	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);
	glDeleteBuffers(1, &lightEBO);
	lightShader.Delete();

	// 프로그램 종료 전 window와 GLFW 해제
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

/*
	Shader : GPU에서 동작하는 프로그램. 입력값과 출력값으로 사용, 실질적으로 이미지를 그림
	VAO : 작업량을 줄이기 위해 VBO들을 연결하여 최종 렌더링된 물체를 저장
	VBO : 그리고자하는 데이터를 넣어두는 GPU의 메모리 버퍼(공간)
	EBO : 인덱스를 이용해서 정점의 순서를 지정하여 저장하는 버퍼(공간)
	Texture : 외부 이미지 파일을 읽어와 출력
	normal : 주어진 표면의 법선(교차점이 하나인 접선의 수직선)과 광원 또는 카메라 방향 사이의 각도
	w : 동치좌표, x,y,z를 각각 나누기, 1이면 공간상에서의 위치, 0이면 방향, 음수는 금지// 방향과 점을 구분하며 mat4와 계산하기 위해 필요 4x4행렬과 계산하기 위해서는 vec4여야함
*/