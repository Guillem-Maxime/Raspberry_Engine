#pragma once

#include "graphicsheader.h"

#include "common/crtphelper.h"
#include "glutils.h"
#include "openglobjecthandler.h"

template<class Derived>
class BufferObjectBase : public OpenGLObjectHandler, public CRTPHelper<Derived, BufferObjectBase>
{
public:
	void Bind() const;
	void BufferData() const;
	void Delete() const;
	void Prepare() const;
	void Unbind() const;

	void PrintErrorMessage(const std::string& errorMessage) const;
	void PrintUninitializedMessage(const std::string& errorMessage) const;
protected:
	virtual void GenerateGLObjectId() override;
	GLuint GetBufferId() const { return m_BufferId; }

	std::string GetBufferTypeString(GLenum bufferType) const;

private:
	GLuint m_BufferId{0};
};


template<class Derived>
void BufferObjectBase<Derived>::Bind() const
{
	if(IsInitialized())
	{
		glBindBuffer( this->Underlying().GetBufferType(), GetBufferId() );
		PrintErrorMessage( "Bind" );
	}
	else
	{
		PrintUninitializedMessage("Bind");
	}
}

template<class Derived>
void BufferObjectBase<Derived>::BufferData() const
{
	glBufferData(this->Underlying().GetBufferType(), this->Underlying().GetBufferSizeOf(), this->Underlying().GetBufferRawData(), this->Underlying().GetBufferUsage());
	PrintErrorMessage("BufferData");
}

template<class Derived>
void BufferObjectBase<Derived>::Delete() const
{
	glDeleteBuffers(1, &m_BufferId);
}

template<class Derived>
void BufferObjectBase<Derived>::Prepare() const
{
	Bind();
	if(IsInitialized())
	{
		this->Underlying().PrepareInternal();
	}
	else
	{
		PrintUninitializedMessage("Prepare");
	}
}

template<class Derived>
void BufferObjectBase<Derived>::Unbind() const
{
	glBindBuffer(this->Underlying().GetBufferType(), 0);
	PrintErrorMessage("Unbind");
}

template<class Derived>
std::string BufferObjectBase<Derived>::GetBufferTypeString(GLenum bufferType) const
{
	switch(bufferType)
	{
		case GL_ARRAY_BUFFER:
			return "ARRAY_BUFFER";
		case GL_ATOMIC_COUNTER_BUFFER:
			return "ATOMIC_COUNTER_BUFFER";
		case GL_COPY_READ_BUFFER:
			return "COPY_READ_BUFFER";
		case GL_COPY_WRITE_BUFFER:
			return "COPY_WRITE_BUFFER";
		case GL_DISPATCH_INDIRECT_BUFFER:
			return "DISPATCH_INDIRECT_BUFFER";
		case GL_DRAW_INDIRECT_BUFFER:
			return "DRAW_INDIRECT_BUFFER";
		case GL_ELEMENT_ARRAY_BUFFER:
			return "ELEMENT_ARRAY_BUFFER";
		case GL_PIXEL_PACK_BUFFER:
			return "PIXEL_PACK_BUFFER";
		case GL_PIXEL_UNPACK_BUFFER:
			return "PIXEL_UNPACK_BUFFER";
		case GL_QUERY_BUFFER:
			return "QUERY_BUFFER";
		case GL_SHADER_STORAGE_BUFFER:
			return "SHADER_STORAGE_BUFFER";
		case GL_TEXTURE_BUFFER:
			return "TEXTURE_BUFFER";
		case GL_TRANSFORM_FEEDBACK_BUFFER:
			return "TRANSFORM_FEEDBACK_BUFFER";
		case GL_UNIFORM_BUFFER:
			return "UNIFORM_BUFFER";
		default:
			return "unknown_buffer_type";
	}
}

template<class Derived>
void BufferObjectBase<Derived>::GenerateGLObjectId()
{
	glGenBuffers(1, &m_BufferId);
	PrintErrorMessage("GenerateGLObject");
}

template<class Derived>
void BufferObjectBase<Derived>::PrintErrorMessage(const std::string& errorMessage) const
{
	if(GLUtils::GetGLError(errorMessage))
	{
		std::cerr << "\tID::" << GetBufferId() << "::BUFFERTYPE::" << GetBufferTypeString(this->Underlying().GetBufferType()) << std::endl;
	}
}

template<class Derived>
void BufferObjectBase<Derived>::PrintUninitializedMessage(const std::string& errorMessage) const
{
	std::cerr << "ID::" << GetBufferId() << "::BUFFERTYPE::" << GetBufferTypeString( this->Underlying().GetBufferType() ) << "::NOT_INITIALIZED and trying to " << errorMessage << std::endl;
}

