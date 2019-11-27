#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "graphics/shader.h"
#include "graphics/program.h"

constexpr GLuint numVAOs{1};
constexpr GLuint numVBOs{1};
constexpr GLuint vPosition{0};

std::string vertexShader = "vert.glsl";

std::string fragmentShader = "frag.glsl";

void InitTriangles(std::array<GLuint,numVAOs>& VAOs, std::array<GLuint,numVBOs>& VBOs);

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
    
    std::array<GLuint,numVAOs> VAOs{};
    std::array<GLuint,numVBOs> VBOs{};

    InitTriangles(VAOs, VBOs);

    while(1)
    {
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glFlush();
    }

    return 0;
}

void InitTriangles(std::array<GLuint,numVAOs>& VAOs, std::array<GLuint, numVBOs>& VBOs)
{
    glGenVertexArrays(numVAOs, VAOs.data());
    glBindVertexArray(VAOs[0]);

    GLfloat vertices[6][3] = 
    {
    	  {-0.90, -0.90, 0.00}
	, { 0.85, -0.90, 0.00}
	, {-0.90,  0.85, 0.00}
	, { 0.90, -0.85, 0.00}
	, { 0.90,  0.90, 0.00}
	, {-0.85,  0.90, 0.00}
    };
    
    Shader vertShader{ {vertexShader, GL_VERTEX_SHADER} };
    Shader fragShader{ {fragmentShader, GL_FRAGMENT_SHADER} };
    Program program({vertShader, fragShader}); 
    program.UseProgram();

    glGenBuffers(numVBOs, VBOs.data());
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(vPosition);
    glBindVertexArray(0);
    
}
