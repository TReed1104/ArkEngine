#ifndef ARKENGINE_LEVEL_H_
#define ARKENGINE_LEVEL_H_
#include <string>
#include <glm/glm.hpp>
#include "JsonParser.hpp"
#include "Tile.h"
#include "BoundingBox.h"
#include "LightSource.h"
#include "SoundEffect.h"
#include "Background.h"

class Engine;

class Level
{
public:
	static Engine* Engine_Pointer;
	int indexOfTileset;
	glm::vec2 tileGridSize;
	glm::vec2 pixelGridSize;
	glm::vec2 playerStartPosition;
	std::vector<Tile*> tileMap;
	std::vector<LightSource*> lightSourcesRegister;
	SoundEffect* backgroundSoundEffect = nullptr;
	Background* levelBackground = nullptr;

	Level(const std::string& filePath);
	~Level(void);

	void Update(const float& deltaTime);
	void Draw(void);
	const std::string GetName(void);
	const std::string GetFilePath(void);
	const std::string GetTileSetName(void);
	const bool IsLoaded(void);
	bool IsTileSolid(const glm::vec2& gridPosition);
	BoundingBox* GetTileBoundingBox(const glm::vec2& gridPosition);
	void Reload(void);
	std::map<std::string, std::string> ExportDataForBinding(void);

private:
	JsonFile* configFile = nullptr;
	std::string name;
	std::string filePath;
	std::string nameOfTilest;
	bool isLoaded;

	bool Load(void);
	bool IsTileValid(const glm::vec2& gridPosition);
};
#endif