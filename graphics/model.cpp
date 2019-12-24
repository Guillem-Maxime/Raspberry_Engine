#include "model.h"

#include <assimp/scene.h>

#include "utils/fileutils.h"

void Model::Load()
{
	const aiScene* scene{ FileUtils::Load3DModel(m_FileName) };
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(const aiNode* node, const aiScene* scene)
{
	for(unsigned int i{0}; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh{ scene->mMeshes[node->mMeshes[i]] };
		m_Mesh.push_back(CreateMesh(mesh, scene));
	}
	for(unsigned int i{0}; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

//temp
Mesh Model::CreateMesh(const aiMesh* mesh, const aiScene* scene)
{
	if(mesh != nullptr && scene != nullptr)
		return Mesh();
	return Mesh();
}
