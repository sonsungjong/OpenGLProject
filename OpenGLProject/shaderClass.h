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
	// ���۷��� ID
	GLuint ID;
public:
	// ������
	shaderClass(const char* vertexFile, const char* fragmentFile);
	// ���
	void Activate();
	// ����
	void Delete();
	// ID ���
	GLuint GetID();
};

#endif