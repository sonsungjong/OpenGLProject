#include "MeshVAO.h"

MeshVAO::MeshVAO()
{
	glGenVertexArrays(1, &ID);
}

void MeshVAO::LinkVBO(MeshVBO VBO, GLuint layout)
{
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.UnBind();
}

void MeshVAO::LinkAttrib(MeshVBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.UnBind();
}

void MeshVAO::Bind()
{
	glBindVertexArray(ID);
}

void MeshVAO::UnBind()
{
	glBindVertexArray(0);
}

void MeshVAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}