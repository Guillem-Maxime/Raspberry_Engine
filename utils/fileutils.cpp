#include "fileutils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ext/stb_image.h"
#include "graphics/graphicsheader.h"

namespace FileUtils
{
	void ReadFile(const std::string& fileName, std::string& outString)
	{
		outString.clear();
		std::ifstream istr(fileName, std::ios_base::ate);
		if(istr.is_open())
		{
			istr.clear();
			istr.seekg(0, std::ios_base::beg);
			std::stringstream sstr;
			sstr << istr.rdbuf();
			istr.close();
			outString = sstr.str();
			std::cout << "READING::FILE::" << fileName << std::endl;
		}
		else
		{
			std::cerr << "UNABLE TO READ FILE : " << fileName << std::endl;
		}
	}

	unsigned char* LoadTexture(const char* fileName, ImageInfos& infos)
	{
		stbi_set_flip_vertically_on_load(true);
		EFileType fileType = GetFileTypeFromExtension(fileName);
		
		std::cout << "LOADING::TEXTURE::" << fileName << std::endl;

		switch(fileType)
		{
			case EFileType::JPG:
			case EFileType::JPEG:
				infos.m_ColorChannel = GL_RGB;
				break;
			case EFileType::PNG:
			case EFileType::Unknown:
				infos.m_ColorChannel = GL_RGBA;
				break;
		}
		return stbi_load(fileName, &infos.m_Width, &infos.m_Height, &infos.m_NbrChannels, 0);
	}

	EFileType GetFileTypeFromExtension(const char* fileName)
	{
		const std::string strFileName{ fileName };
		size_t pos{ strFileName.find(".") };
		if( pos == std::string::npos)
		{
			std::cerr << "ERROR this file " << strFileName << " has no extension !" << std::endl;
			return EFileType::Unknown;
		}

		const std::string extension{ strFileName.substr(pos, strFileName.size()) };
		if( extension == ".jpg" )
		{
			return EFileType::JPG;
		}
		else if( extension == ".jpeg" ) 
		{
			return EFileType::JPEG;
		}
		else if( extension == ".png" ) 
		{
			return EFileType::PNG;
		}
		else
		{
			return EFileType::Unknown;
		}
	}

	const aiScene* Load3DModel(const std::string& fileName)
	{
		Assimp::Importer importer;
		return importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs);
	}
} //FileUtils
