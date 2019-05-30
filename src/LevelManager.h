#ifndef ARKENGINE_LEVELMANAGER_H_
#define ARKENGINE_LEVELMANAGER_H_

#include <vector>
#include "Level.h"

class LevelManager {
public:
	static LevelManager& GetInstance();
	LevelManager(LevelManager const&) = delete;
	void operator=(LevelManager const&) = delete;

	void RegisterLevel(Level& newLevel);
	const int GetIndexOfLevel(const std::string& levelName);
	const Level* GetLevel(const std::string& levelName);
	const Level* GetCurrentLevel(void);
	bool SetCurrentLevel(const std::string& levelName);

private:
	std::vector<Level*> levelRegister;
	int indexOfCurrentLevel = -1;

	LevelManager() {}

};

#endif