#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include "graphics/camera.h"
#include "graphics/shaderhandler.h"
#include "graphics/programhandler.h"
#include "graphics/glutils.h"
#include "graphics/vertex.h"
#include "graphics/mesh.h"
#include "graphics/texturehandler.h"
#include "graphics/vbohandler.h"
#include "graphics/vaohandler.h"

static std::string vertexShader = "vert.glsl";
static std::string fragmentShader = "frag.glsl";
static std::string testTextureFile = "xmen.png";

void InitOpenGL();
void InitTriangles(VAOInitializer& vao1, VAOInitializer& vao2);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	InitOpenGL();

    ShaderInfos vertShaderInfos;
   	vertShaderInfos.m_ShaderName = vertexShader;
	vertShaderInfos.m_ShaderType = GL_VERTEX_SHADER;
    ShaderInfos fragShaderInfos;
   	fragShaderInfos.m_ShaderName = fragmentShader;
	fragShaderInfos.m_ShaderType = GL_FRAGMENT_SHADER;
    
	ProgramInitializer programInit;
   	programInit.m_ShaderInfos.reserve(2);
	programInit.m_ShaderInfos.push_back(vertShaderInfos);
	programInit.m_ShaderInfos.push_back(fragShaderInfos); 

	TextureInfos textureInfos;
	textureInfos.m_TextureFile = testTextureFile;
	textureInfos.m_TextureType = GL_TEXTURE_2D;
    
	glm::mat4 model{ glm::mat4(1.0f) };
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  	
	Camera camera;
	camera.Init();

	VAOInitializer vaoInit1, vaoInit2;
	vaoInit1.m_ProgramInitializer = programInit;
	vaoInit1.m_TextureInfos = textureInfos;
	vaoInit1.m_Camera = &camera;

	vaoInit2.m_ProgramInitializer = programInit;
	vaoInit2.m_TextureInfos = textureInfos;
	vaoInit2.m_Camera = &camera;

    InitTriangles(vaoInit1, vaoInit2);

	VAOHandler vao1;
	vao1.Init(vaoInit1);
	vao1.Prepare();
	vao1.AddModelTransform(model);

	VAOHandler vao2;
	vao2.Init(vaoInit2);
	vao2.Prepare();
	vao2.AddModelTransform(model);

    ShaderInfos simpleVertShaderInfos;
   	simpleVertShaderInfos.m_ShaderName = "simplevert.glsl";
	simpleVertShaderInfos.m_ShaderType = GL_VERTEX_SHADER;
    ShaderInfos simpleFragShaderInfos;
   	simpleFragShaderInfos.m_ShaderName = "simplefrag.glsl";
	simpleFragShaderInfos.m_ShaderType = GL_FRAGMENT_SHADER;
	
	ProgramInitializer simpleProgramInit;
    simpleProgramInit.m_ShaderInfos.push_back(simpleVertShaderInfos);
	simpleProgramInit.m_ShaderInfos.push_back(simpleFragShaderInfos);
	
	std::vector<Vertex1P1N1U> vertices{};
	vertices.reserve(3);
   	Vertex1P1N1U v1, v2, v3;
    v1.m_Position = {-0.5, -0.5, 0.00};
    v1.m_Texture = {0.0, 0.0};
    v2.m_Position = { 0.5, -0.5, 0.00};
    v2.m_Texture = {1.0, 0.0};
    v3.m_Position = { 0.0,  0.5, 0.00};
    v3.m_Texture = {0.0, 1.0};
    vertices.push_back(v1);
    vertices.push_back(v2);
	vertices.push_back(v3);
	Mesh mesh;
	mesh.SetVertices(vertices);

	VBOInfos vboInfos;
	vboInfos.m_Mesh = mesh;
	VBOHandler vbo;
	vbo.Init(vboInfos);

	VAOInitializer vao3Init;
	vao3Init.m_ProgramInitializer = simpleProgramInit;
	vao3Init.m_VBOInfos = vboInfos;
	vao3Init.m_TextureInfos = textureInfos;
	vao3Init.m_Camera = &camera;

	VAOHandler vao3;
	vao3.Init(vao3Init);
	vao3.Prepare();
	vao3.Unbind();

	std::cout << "Drawing Loop" << std::endl;
	int frameCount{0};
    //while(frameCount < 3)
    while(1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		GLUtils::GetGLError("glClear");
		vao1.Draw();	
		//vao2.Draw();
		//vao3.Draw();
		glFlush();
		GLUtils::GetGLError("glFlush");
		glutSwapBuffers();
		frameCount++;
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void InitTriangles(VAOInitializer& vaoInit1, VAOInitializer& vaoInit2)
{ 	
	std::vector<Vertex1P1N1U> firstVertices{};
	firstVertices.reserve(3);
   	Vertex1P1N1U v11, v12, v13, v14;
    v11.m_Position = {-0.90, -0.90, 0.00};
    v11.m_Texture = {0.0, 0.0};
    v12.m_Position = { 0.90, -0.90, 0.00};
    v12.m_Texture = {1.0, 0.0};
    v13.m_Position = { 0.90,  0.90, 0.00};
    v13.m_Texture = {1.0, 1.0};
    v14.m_Position = {-0.90,  0.90, 0.00};
    v14.m_Texture = {0.0, 1.0};
    firstVertices.push_back(v11);
    firstVertices.push_back(v12);
	firstVertices.push_back(v13);
	firstVertices.push_back(v14);
	std::vector<GLuint> indices;
	indices.reserve(6);
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	Mesh firstMesh;
	firstMesh.SetVertices(firstVertices);
	firstMesh.SetIndices(indices);
	VBOInfos firstVBOInfos;
	firstVBOInfos.m_Mesh = firstMesh;
	EBOInfos firstEBOInfos;
	firstEBOInfos.m_Indices = indices;
	vaoInit1.m_VBOInfos = firstVBOInfos;
	vaoInit1.m_EBOInfos = firstEBOInfos;

	std::vector<Vertex1P1N1U> secondVertices{};
	secondVertices.reserve(3);
    Vertex1P1N1U v4, v5, v6;
    v4.m_Position = { 0.90,-0.85, 0.00};
	v4.m_Texture = {1.0, 0.0};
    v5.m_Position = { 0.90, 0.90, 0.00};
	v5.m_Texture = {1.0, 1.0};
    v6.m_Position = {-0.85, 0.90, 0.00};
	v6.m_Texture = {0.0, 1.0};
    secondVertices.push_back(v4);
    secondVertices.push_back(v5);
	secondVertices.push_back(v6);
	Mesh secondMesh;
	secondMesh.SetVertices(secondVertices);
	VBOInfos secondVBOInfos;
	secondVBOInfos.m_Mesh = secondMesh;
   	vaoInit2.m_VBOInfos = secondVBOInfos;	   
}
