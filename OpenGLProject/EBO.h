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

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void UnBind();
	// Deletes the EBO
	void Delete();
};

#endif