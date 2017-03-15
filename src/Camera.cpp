#include "Camera.h"
#include "Tile.h"
#include "Engine.h"
#include "GameObject.h"

Camera::Camera(Engine &engine, const glm::vec3& cameraPosition, const glm::vec3& cameraLookAt, const glm::vec3& upVector, const glm::mat4& projectionMatrix) {
	// Initialise the Camera.
	this->engine = &engine;
	this->position = cameraPosition;
	this->lookAt = cameraLookAt;
	this->upVector = upVector;
	this->viewMatrix = glm::lookAt(cameraPosition, cameraLookAt, upVector);
	this->projectionMatrix = projectionMatrix;
}
Camera::~Camera() {

}

void Camera::Update(const float& deltaTime, const GameObject& object) {
	if (controlMode == CameraMode::FreeFollow || controlMode == CameraMode::LockedFollow) {
		FollowObject(object);
	}
	else if (controlMode == CameraMode::Manual) {
		ManualControl();
	}
	viewMatrix = glm::lookAt(position, lookAt, upVector);	// Update the ViewMatrix.
}
void Camera::FollowObject(const GameObject& object) {
	if (engine->player != nullptr) {
		position = glm::vec3(engine->player->position.x, engine->player->position.y, position.z);
		lookAt = glm::vec3(position.x, position.y, lookAt.z);
	}
}
void Camera::ManualControl(void) {

}
void Camera::SetControlMode(const CameraMode& newMode) {

}