#pragma once
#include <glad/glad.h>
#include "MeshVBO.h"
class MeshVAO
{
protected:
	GLuint ID;
public:
	// 기본 생성자
	MeshVAO();

	void LinkVBO(MeshVBO VBO, GLuint layout);
	void LinkAttrib(MeshVBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void UnBind();
	void Delete();
};

