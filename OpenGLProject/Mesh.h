#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>

#include "MeshVAO.h"
#include "MeshEBO.h"
#include "Texture.h"
#include "Camera.h"

class Mesh
{
protected:
	MeshVAO VAO;
	
public:
	std::vector <Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
	
	void Draw(shaderClass& shader, Camera& camera);
};

#endif