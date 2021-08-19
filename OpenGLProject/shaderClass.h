#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class shaderClass
{
protected:
	// 레퍼런스 ID
	GLuint ID;
public:
	// 생성자
	shaderClass(const char* vertexFile, const char* fragmentFile);
	// 사용
	void Activate();
	// 해제
	void Delete();
	// ID 사용
	GLuint GetID();
};

#endif