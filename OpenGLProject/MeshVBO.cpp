#include "MeshVBO.h"
// Vertex Buffer Object�� �����ϰ� vertices�� �����ϴ� ������
MeshVBO::MeshVBO(std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void MeshVBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void MeshVBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshVBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
