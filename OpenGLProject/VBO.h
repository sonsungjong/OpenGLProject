#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
protected:
	GLuint ID;
public:
	// »ý¼ºÀÚ
	VBO(GLfloat* vetices, GLsizeiptr size);

	void Bind();
	void UnBind();
	void Delete();
};

#endif