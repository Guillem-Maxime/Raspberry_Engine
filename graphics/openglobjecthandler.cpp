#include "openglobjecthandler.h"

void OpenGLObjectHandler::InitInternal()
{ 
	m_IsInitialized = true; 
	GenerateGLObjectId();
}

