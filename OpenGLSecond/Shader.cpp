#include "Shader.h"

// text������ �а� string���� ���
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

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// vertex���ϰ� fragment������ �а� string���� ����
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// string�� char* �� ��ȯ
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

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
	ID = glCreateProgram();
	// Vertex ���̴��� Fragment ���̴��� Shader Program�� ���δ�
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// shaderProgram�� Link
	glLinkProgram(ID);

	// ��������ʴ� Vertex�� Fragment ���̴� ��ü�� �����Ѵ�.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// ���
void Shader::Activate()
{
	glUseProgram(ID);
}

// ����
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::Rotation() {
	// ȸ��
	trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glUseProgram(ID);
	glUniformMatrix4fv(glGetUniformLocation(ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
}

void Shader::RotationRepeat() {
	// ȸ��
	trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
}