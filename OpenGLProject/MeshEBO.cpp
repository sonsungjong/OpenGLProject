#include "MeshEBO.h"
// Element Buffer Object�� �����ϰ� indices�� �����ϴ� ������
MeshEBO::MeshEBO(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

}

void MeshEBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void MeshEBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void MeshEBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
