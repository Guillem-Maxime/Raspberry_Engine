#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "graphics/shaderhandler.h"
#include "graphics/programhandler.h"
#include "graphics/vertex.h"
#include "graphics/mesh.h"
#include "graphics/vbohandler.h"
#include "graphics/vaohandler.h"

std::string vertexShader = "vert.glsl";

std::string fragmentShader = "frag.glsl";

void InitOpenGL();
void InitTriangles(VAOHandler& vao1, VAOHandler& vao2);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	InitOpenGL();

    ShaderHandler vertShader{ {vertexShader, GL_VERTEX_SHADER} };
    ShaderHandler fragShader{ {fragmentShader, GL_FRAGMENT_SHADER} };
    ProgramHandler program({vertShader, fragShader}); 

    VAOHandler vao1(program);
	VAOHandler vao2(program);

    InitTriangles(vao1, vao2);

    while(1)
    {
		glClear(GL_COLOR_BUFFER_BIT);
		vao1.Draw();
		vao2.Draw();
		glFlush();
    }

    return 0;
}

void InitOpenGL()
{
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Hello Window");
    
    if(glewInit())
    {
        std::cerr << "Unable to Initialize glew" << std::endl;
    }
}

void InitTriangles(VAOHandler& vao1, VAOHandler& vao2)
{
    vao1.Bind();
    	
	std::vector<Vertex1P1N1U> firstVertices{};
	firstVertices.reserve(3);
   	Vertex1P1N1U v1, v2, v3;
    v1.m_Position = {-0.90, -0.90, 0.00};
    v2.m_Position = { 0.85, -0.90, 0.00};
    v3.m_Position = {-0.90,  0.85, 0.00};
    firstVertices.push_back(v1);
    firstVertices.push_back(v2);
	firstVertices.push_back(v3);
	Mesh firstMesh;
	firstMesh.SetVertices(firstVertices);
	VBOInitializer firstVBOInit{firstMesh};
	VBOHandler firstVBO{firstVBOInit};
    
	vao1.SetVBO(firstVBO);
	vao1.Compute();
    vao1.Unbind();
 
	vao2.Bind();

	std::vector<Vertex1P1N1U> secondVertices{};
	secondVertices.reserve(3);
    Vertex1P1N1U v4, v5, v6;
    v4.m_Position = { 0.90,-0.85, 0.00};
    v5.m_Position = { 0.90, 0.90, 0.00};
    v6.m_Position = {-0.85, 0.90, 0.00};
    secondVertices.push_back(v4);
    secondVertices.push_back(v5);
	secondVertices.push_back(v6);
	Mesh secondMesh;
	secondMesh.SetVertices(secondVertices);
	VBOInitializer secondVBOInit{secondMesh};
	VBOHandler secondVBO{secondVBOInit};
    
	vao2.SetVBO(secondVBO);
	vao2.Compute();
	vao2.Unbind();
    
}
