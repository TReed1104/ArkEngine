#ifndef ShaderComponents_h_included
#define ShaderComponents_h_included

// Header file Includes.
#include <GL/glew.h>

class VertexShaderComponents {
public:
	GLint vertexPositionAttrib;
	GLint colourAttrib;
	GLint uvAttrib;
	GLint modelMatrixUniform;
	GLint viewMatrixUniform;
	GLint projectionMatrixUniform;

	VertexShaderComponents() {}
	~VertexShaderComponents() {}
};

class FragementShaderComponents
{
public:
	GLint hasTextureUniform;
	GLint textureSamplerUniform;

	// Constructors and Deconstructors
	FragementShaderComponents() {}
	~FragementShaderComponents() {}
};
#endif