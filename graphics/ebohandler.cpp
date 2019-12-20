#include "ebohandler.h"

void EBOHandler::Init(const EBOInfos& infos)
{
	InitInternal();
	m_Indices = infos.m_Indices;
	m_BufferUsage = infos.m_BufferUsage;
	m_DrawMode = infos.m_DrawMode;
}

void EBOHandler::PrepareInternal() const
{
	BufferData();
}

void EBOHandler::Draw() const
{
	Bind();
	glDrawElements(m_DrawMode, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, 0);
	PrintErrorMessage("EBODraw");
}
