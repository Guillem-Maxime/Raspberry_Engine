#pragma once

#include "graphics/graphicsheader.h"

#include "graphics/mesh.h"

struct aiNode;
struct aiScene;
struct aiMesh;

class Model
{
public:

	void Load();
	void ProcessNode(const aiNode* node, const aiScene* scene);
	Mesh CreateMesh(const aiMesh* mesh, const aiScene* scene);

private:
	std::string m_FileName;
	std::vector<Mesh> m_Mesh{};
};
