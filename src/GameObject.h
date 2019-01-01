#ifndef ARKENGINE_GAMEOBJECT_H_
#define ARKENGINE_GAMEOBJECT_H_

#include <string>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL_image.h>
#include "Model.h"
#include "Texture.h"
#include "Animation.h"
#include "BoundingBox.h"
#include "LuaScript.h"

class Engine;

class GameObject {
public:
	static Engine* Engine_Pointer;

	std::vector<Animation> animations;
	int animationIndex;

	// Shader indexer
	int indexOfCurrentShader;

	// Model and texture variables
	LuaScript* script;
	Model model;
	const Texture* texture;
	glm::ivec2 sourceFrameSize;
	glm::ivec2 sourceFramePosition;

	// Positions
	glm::vec3 position;			// The world position of the object
	glm::ivec2 gridPosition;	// The current grid cell the object is counted as being within.
	glm::ivec2 drawOffset;		// The offset the sprite is to be drawn in relation to the world position.
	glm::vec3 drawPosition;		// Position to draw to the screen, this takes into account the offset of the object to its texture

	// Bounding Boxes
	BoundingBox boundingBox;
	glm::vec2 boundingBoxOffset;

	// Movement Physics
	glm::vec2 velocity;
	const float baseMovementSpeed = 80.0f;
	const float maxMovementSpeed = 120.0f;
	float currentMovementSpeed;

	const float timeForMaxFall = 1.5f;
	const float baseFallingSpeed = 2.0f;
	const float maxFallingSpeed = 200.0f;
	float currentFallingSpeed;
	float fallTimer;

	const float timeForMaxJump = 0.8f;
	const float baseJumpingSpeed = -120.0f;
	float currentJumpingSpeed;
	float jumpingTimer;
	
	// Transformations
	float rotation;
	glm::vec3 scale;
	
	GameObject(const std::string& scriptPath = "NO SCRIPT");
	~GameObject(void);

	void Update(const float& deltaTime);
	void Draw(void);
	void Reposition(const glm::vec2& newPosition);

private:
	void UpdatePosition(void);
	void UpdateRotation(void);
	void UpdateScale(void);
	void LoadAnimations(void);
	void HandleAnimations(const float& deltaTime);

protected:
	virtual void UpdateAnimationState(void);
	virtual void UpdateAnimationIndex(void);

};

#endif
