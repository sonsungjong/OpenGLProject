#include "shaderClass.h"

// text파일을 읽고 string으로 출력
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}

shaderClass::shaderClass(const char* vertexFile, const char* fragmentFile)
{
	// vertex파일과 fragment파일을 읽고 string으로 저장
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// string을 char* 로 변환
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

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
	ID = glCreateProgram();
	// Vertex 쉐이더와 Fragment 쉐이더를 Shader Program에 붙인다
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// shaderProgram을 Link
	glLinkProgram(ID);

	// 사용하지않는 Vertex와 Fragment 쉐이더 객체를 해제한다.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// 사용
void shaderClass::Activate()
{
	glUseProgram(ID);
}

// 해제
void shaderClass::Delete()
{
	glDeleteProgram(ID);
}

GLuint shaderClass::GetID()
{
	return ID;
}