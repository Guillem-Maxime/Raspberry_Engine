#include "model.h"

#include <algorithm>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "graphics/openglrendermanager.h"

#include "utils/fileutils.h"

void Model::Load()
{
	FileUtils::Load3DModel(m_FileName, m_Meshes, m_TexturesLoaded);
	for(const auto& mPtr : m_Meshes)
	{
		Mesh* mesh{ mPtr.get() };
		if(mesh != nullptr)
		{
			OpenGLRenderManager::Get()->RegisterToRender(mesh);
		}
		else
		{
			std::cerr << "ERROR::NO:3D:MODEL:LOADED" << std::endl;
		}
	}
}

void Model::RegisterPosition(glm::mat4* position)
{
	std::for_each(m_Meshes.begin(), m_Meshes.end(), 
	[position](auto& mPtr) { mPtr.get()->RegisterPosition(position); });
}

void Model::UnregisterPosition(glm::mat4* position)
{
	std::for_each(m_Meshes.begin(), m_Meshes.end(), 
	[position](auto& mPtr) { mPtr.get()->UnregisterPosition(position); });
}