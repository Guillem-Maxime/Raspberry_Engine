#include "glutils.h"

namespace GLUtils
{
	bool GetGLError(const std::string& log)
	{
		const GLenum error{ glGetError() };
		bool result{true};
		switch(error)
		{
			case GL_NO_ERROR :
				result = false;
				break;
			case GL_INVALID_ENUM :
				std::cerr << error << "::" << log << "::INVALID::ENUM" << std::endl;
				break;
			case GL_INVALID_VALUE :
				std::cerr << error << "::" << log << "::INVALID::VALUE" << std::endl;
				break;
			case GL_INVALID_OPERATION :
				std::cerr << error << "::" << log <<"::INVALID::OPERATION" << std::endl;
				break;
			case GL_STACK_OVERFLOW :
				std::cerr << error << "::" << log << "::STACK::OVERFLOW" << std::endl;
				break;
			case GL_STACK_UNDERFLOW :
				std::cerr << error << "::" << log << "::STACK::UNDERFLOW" << std::endl;
				break;
			case GL_OUT_OF_MEMORY :
				std::cerr << error << "::" << log << "::OUT::OF::MEMORY" << std::endl;
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION :
				std::cerr << error << "::" << log << "::INVALID::FRAMEBUFFER::OPERATION" << std::endl;
				break;
			default:
				std::cerr << error << "::" << log << "::BAD::ERROR::ENUM" << std::endl;
				break;
		}
		return result;
	}
}//GLUtils
