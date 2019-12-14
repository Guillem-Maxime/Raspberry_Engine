#version 330 core

out vec4 fColor;

in vec3 normal;
in vec2 textureCoord;

uniform sampler2D textureSampler;

void main()
{
	fColor = texture(textureSampler, textureCoord);
}
