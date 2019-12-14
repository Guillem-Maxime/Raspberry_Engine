#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexture;

uniform mat4 mProjView;
uniform mat4 mModel;

out vec3 normal;
out vec2 textureCoord;

void main()
{
	gl_Position = mProjView * mModel * vec4(vPosition, 0.0f);
	normal = vNormal;
	textureCoord = vTexture;
}
