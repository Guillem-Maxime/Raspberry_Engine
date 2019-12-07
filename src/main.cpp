#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "graphics/shader.h"
#include "graphics/program.h"
#include "graphics/vertex.h"
#include "graphics/mesh.h"
#include "graphics/vbohandler.h"
#include "graphics/vaohandler.h"

std::string vertexShader = "vert.glsl";

std::string fragmentShader = "frag.glsl";

void InitTriangles(VAOHandler& vao);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Hello Window");
    
    if(glewInit())
    {
        std::cerr << "Unable to Initialize glew" << std::endl;
    }

    Shader vertShader{ {vertexShader, GL_VERTEX_SHADER} };
    Shader fragShader{ {fragmentShader, GL_FRAGMENT_SHADER} };
    Program program({vertShader, fragShader}); 

    VAOHandler vao(program);

    InitTriangles(vao);

    while(1)
    {
	glClear(GL_COLOR_BUFFER_BIT);
	vao.Draw();
	glFlush();
    }

    return 0;
}

void InitTriangles(VAOHandler& vao)
{
    vao.Bind();
    	
	std::vector<Vertex1P1N1U> firstVertices{};
	firstVertices.reserve(3);
   	Vertex1P1N1U v1, v2, v3;
    v1.m_Position = {-0.90, -0.90, 0.00};
    v2.m_Position = { 0.85, -0.90, 0.00};
    v3.m_Position = {-0.90,  0.85, 0.00};
    firstVertices.push_back(v1);
    firstVertices.push_back(v2);
	firstVertices.push_back(v3);
	Mesh firstMesh(firstVertices);

	VBOInitializer firstVBOInit{firstMesh};
	VBOHandler firstVBO{firstVBOInit};
    
	vao.AddVBO(firstVBO);
	
	//firstVBO.Compute();
   	//firstVBO.Unbind(); 
    //glBindVertexArray(0);
 
	//glBindVertexArray(VAOs[1]);

	std::vector<Vertex1P1N1U> secondVertices{};
	secondVertices.reserve(3);
    Vertex1P1N1U v4, v5, v6;
    v4.m_Position = { 0.90,-0.85, 0.00};
    v5.m_Position = { 0.90, 0.90, 0.00};
    v6.m_Position = {-0.85, 0.90, 0.00};
    secondVertices.push_back(v4);
    secondVertices.push_back(v5);
	secondVertices.push_back(v6);
	Mesh secondMesh(secondVertices);

	VBOInitializer secondVBOInit{secondMesh};
	VBOHandler secondVBO{secondVBOInit};
    
	vao.AddVBO(secondVBO);
	//secondVBO.Compute();
    
	vao.Compute();
	vao.Unbind();
    
}
