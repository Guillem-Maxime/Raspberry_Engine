#include "fileutils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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
		}
		else
		{
			std::cerr << "UNABLE TO READ FILE : " << fileName << std::endl;
		}
	}
} //FileUtils
