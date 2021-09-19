#pragma once
#include <glad/glad.h>
#include <vector>
class MeshEBO
{
protected:
	GLuint ID;
public:
	// ������
	MeshEBO(std::vector<GLuint>& indices);

	void Bind();
	void UnBind();
	void Delete();
};

