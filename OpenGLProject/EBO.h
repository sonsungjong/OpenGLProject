#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
protected:
	GLuint ID;
public:
	// »ý¼ºÀÚ
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void UnBind();
	void Delete();
};

#endif