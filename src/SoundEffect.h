#ifndef ARKENGINE_SOUNDEFFECT_H_
#define ARKENGINE_SOUNDEFFECT_H_

#include <string>
#include <SDL.h>
#include <glm/glm.hpp>
#include <AL/al.h>
#include <AL/alc.h>

class Engine;

class SoundEffect {
public:
	static Engine* Engine_Pointer;

	enum SoundType { SOUND_EFFECT, BACKGROUND };

	SoundEffect(const std::string& soundName = "NOT SET", const std::string& filePath = "NOT SET", const SoundType& type = SoundType::SOUND_EFFECT, const bool& isLooped = false, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& velocity = glm::vec3(0.0f), const float& pitch = 1.0f, const float& gain = 1.0f);
	~SoundEffect();
	
	// Gets
	const std::string GetName(void);
	const SoundType GetSoundType(void);
	const bool IsLoaded(void);
	const bool IsLooped(void);
	const float GetPitch(void);
	const float GetGain(void);
	const glm::vec3 GetPosition(void);
	const glm::vec3 GetVelocity(void);
	
	// Sets
	void SetSoundType(const SoundType& newType);
	void SetLoopState(const bool& newLoopState);
	void SetPitch(const float& newPitch);
	void SetGain(const float& newGain);
	void SetPosition(const glm::vec3& newPosition);
	void SetVelocity(const glm::vec3& newVelocity);

	// Playback functions
	void Play(void);
	void Pause(void);
	void Stop(void);
	void Restart(void);

private:
	std::string name;
	SoundType type;
	bool isLoaded = false;
	bool isLooped = false;
	float pitch = 1.0f;
	float gain = 1.0f;
	glm::vec3 position = glm::vec3(0);
	glm::vec3 velocity = glm::vec3(0);

	ALuint alBuffer;
	ALuint alSource;

	bool CheckOpenALErrors(void);
	bool LoadSource(void);
	bool LoadBuffer(const std::string& filePath);

};

#endif