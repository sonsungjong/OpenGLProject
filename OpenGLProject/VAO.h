#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
protected:
	GLuint ID;
public:
	// 기본 생성자
	VAO();

	void LinkVBO(VBO VBO, GLuint layout);
	void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void UnBind();
	void Delete();
};

#endif