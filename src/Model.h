#ifndef ARKENGINE_MODEL_H_
#define ARKENGINE_MODEL_H_

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ShaderPointers.hpp"

class Engine;

class Model
{
public:
	class Mesh
	{
	public:
		// Buffers where the data about the mesh are stored for use by OpenGL
		GLuint vertexBufferObject;
		GLuint indicesBufferObject;
		GLuint colourBufferObject;
		GLuint uvBufferObject;
		GLuint vertexArrayObject;

		// The attributes of the mesh itself.
		bool isSetupForTextures;
		std::vector<glm::vec3> vertexPositions;
		std::vector<unsigned int> indices;
		std::vector<glm::vec3> colourData;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> surfaceNormals;

		Mesh();
		~Mesh();

		void SetParent(const Model& parentModel);
		void GenerateVertexBuffers();
		void GenerateVertexArrayObject(const ShaderPointers& shaderPointers);
		void SetTranslation(bool isModelUpdate = false, const glm::vec3& translation = glm::vec3(0.0f));
		void SetRotation(bool isModelUpdate = false, const float& rotationAngle = 0.0f, const glm::vec3& rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f));
		void SetScale(bool isModelUpdate = false, const glm::vec3& scale = glm::vec3(1.0f));
		glm::mat4 GetModelMatrix();

	private:
		const Model* parent;
		glm::vec3 currentTranslation;
		float currentRotationAngle;
		glm::vec3 currentRotationAxis;
		glm::vec3 currentScale;

		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;
	};

	std::string name;
	std::vector<Mesh> meshes;

	Model() {}
	Model(const Engine& engine, const std::string& name = "");
	~Model();

	void SetVertexObjects();
	void SetMeshParents();
	void Translate(const glm::vec3& translation = glm::vec3(0.0f));
	void Rotate(const float& rotationAngle = 0.0f, const glm::vec3& rotationAxis = glm::vec3(0.0f));
	void Scale(const glm::vec3& scale = glm::vec3(0.0f));
	void SetMeshTranslation(const int& indexOfMesh, const glm::vec3& translation = glm::vec3(0.0f));
	void SetMeshRotation(const int& indexOfMesh, const float& rotationAngle = 0.0f, const glm::vec3& rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f));
	void SetMeshScale(const int& indexOfMesh, const glm::vec3& scale = glm::vec3(0.0f));

private:
	const Engine* engine;
	glm::mat4 modelTranslationMatrix;
	glm::mat4 modelRotationMatrix;
	glm::mat4 modelScaleMatrix;
};
#endif