#include "LevelManager.h"

LevelManager* LevelManager::GetInstance() {
	static LevelManager instance;
	return &instance;
}

void LevelManager::RegisterLevel(Level* newLevel) {
	levelRegister.push_back(newLevel);
}
void LevelManager::Close(void) {
	// Delete all the levels.
	for (Level* level : levelRegister) {
		delete level;
		level = nullptr;
	}
}
const int LevelManager::GetIndexOfLevel(const std::string & levelName) {
	int indexOfLevel = -1;
	const size_t numberOfLevels = levelRegister.size();
	for (size_t i = 0; i < numberOfLevels; i++) {
		if (levelRegister[i]->GetName() == levelName) {
			indexOfLevel = (int)i;
		}
	}
	return indexOfLevel;
}
Level* LevelManager::GetLevel(const std::string& levelName) {
	int indexOfLevel = -1;
	const size_t numberOfLevels = levelRegister.size();
	for (size_t i = 0; i < numberOfLevels; i++) {
		if (levelRegister[i]->GetName() == levelName) {
			indexOfLevel = (int)i;
		}
	}
	if (indexOfLevel == -1) {
		return nullptr;
	}
	return levelRegister[indexOfLevel];
}
Level* LevelManager::GetCurrentLevel(void) {
	if (indexOfCurrentLevel == -1 || indexOfCurrentLevel > levelRegister.size()) {
		return nullptr;
	}
	else {
		return levelRegister[indexOfCurrentLevel];
	}
}
bool LevelManager::SetCurrentLevel(const std::string& levelName) {
	int indexOfNewLevel = GetIndexOfLevel(levelName);
	if (indexOfNewLevel != -1) {
		indexOfCurrentLevel = indexOfNewLevel;
		return true;
	}
	else {
		return false;
	}
}
bool LevelManager::Update(const float& deltaTime) {
	if (indexOfCurrentLevel == -1 || indexOfCurrentLevel > levelRegister.size()) {
		return false;
	}
	else {
		levelRegister[indexOfCurrentLevel]->Update(deltaTime);
		return true;
	}
}
bool LevelManager::Render(void) {
	if (indexOfCurrentLevel == -1 || indexOfCurrentLevel > levelRegister.size()) {
		return false;
	}
	else {
		levelRegister[indexOfCurrentLevel]->Draw();
		return true;
	}
}
