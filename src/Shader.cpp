#include "Shader.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	vertexFilePath = vertexShaderPath;
	fragmentFilePath = fragmentShaderPath;
}
Shader::~Shader() {

}

bool Shader::ReadFile(std::string& rawString, const std::string& strShaderFile) {
	// Read the Shader file
	rawString = "";
	std::ifstream fileReader(strShaderFile);
	if (!fileReader.is_open()) {
		std::cout << "Shader file not found - " << strShaderFile << std::endl;
		return false;
	}
	std::string line = "";
	while (getline(fileReader, line)) {
		rawString += line + "\n";
	}
	fileReader.close();
}
bool Shader::ImportShaderFiles() {
	if (ReadFile(rawVertexString, vertexFilePath)) {
		if (ReadFile(rawFragmentString, fragmentFilePath)) {
			// As both the shader files were parsed correctly into memory, return true.
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
bool Shader::CreateShader(GLuint& shaderID, const GLenum& eShaderType, const std::string& strShaderFile) {
	shaderID = glCreateShader(eShaderType);
	// Error check
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shaderID, 1, &strFileData, NULL);
	glCompileShader(shaderID);

	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (!status) {
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (eShaderType) {
		case GL_VERTEX_SHADER:
			strShaderType = "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			strShaderType = "fragment";
			break;
		}
		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
		return false;
	}
	return true;
}
bool Shader::CompileShader() {
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	// Create the Vertex Shader
	if (CreateShader(vertexShaderID, GL_VERTEX_SHADER, rawVertexString)) {
		// Create the Fragment Shader
		if (CreateShader(fragmentShaderID, GL_FRAGMENT_SHADER, rawFragmentString)) {
			// Both Shaders were created, attach them to the program.
			this->program = glCreateProgram();
			glAttachShader(this->program, vertexShaderID);
			glAttachShader(this->program, fragmentShaderID);
			glLinkProgram(this->program);

			GLint status;
			glGetProgramiv(this->program, GL_LINK_STATUS, &status);

			if (!status) {
				// If the program or shaders fail, print the errors.
				GLint infoLogLength;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar *strInfoLog = new GLchar[infoLogLength + 1];
				glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
				fprintf(stderr, "Linker failure: %s\n", strInfoLog);
				delete[] strInfoLog;
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);
				return false;
			}
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
			return true;
		}
		else {
			std::cout << "Failed to create Fragment Shader" << std::endl;
			return false;
		}
	}
	else {
		std::cout << "Failed to create Vertex Shader" << std::endl;
		return false;
	}
}
bool Shader::Load(void) {
	// Import the shader files
	if (ImportShaderFiles()) {
		// Compile the Shaders and attach them to the program
		if (CompileShader()) {
			// The Shader has been successfully created, return true
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
void Shader::Activate(void) {
	// Tells the engine to use this shader for the Current Draw.
	glUseProgram(program);
}
