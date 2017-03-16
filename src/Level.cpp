#include "Level.h"
#include "Engine.h"

Level::Level(const Engine& engine, const std::string & filePath) {
	this->engine = &engine;
	Load(filePath);
}

Level::~Level() {
	delete script;
	for (int i = 0; i < tileMap.size(); i++) {
		delete tileMap[i];
	}
}

void Level::Update(float deltaTime) {
	for (int y = 0; y < tileGridSize.y; y++) {
		for (int x = 0; x < tileGridSize.x; x++) {
			int index = y * tileGridSize.x + x;
			tileMap[index]->Update(deltaTime);
		}
	}
}

void Level::Draw() {
	for (int y = 0; y < tileGridSize.y; y++) {
		for (int x = 0; x < tileGridSize.x; x++) {
			int index = y * tileGridSize.x + x;
			tileMap[index]->Draw();
		}
	}
}

void Level::Load(const std::string & filePath) {
	// Load the information from the script
	script = new LuaScript(filePath);
	if (script->isScriptLoaded) {
		// Grab the data from the script.
		nameOfTilest = script->Get<std::string>("map.tileset_name");
		tileGridSize = glm::vec2(script->Get<int>("map.tile_grid_size.x"), script->Get<int>("map.tile_grid_size.y"));
		playerStartPosition = glm::vec2(script->Get<int>("map.player_start_grid_position.x"), script->Get<int>("map.player_start_grid_position.y"));
		std::vector<int> rawMapData = script->GetVector<int>("map.map_data");

		// Find the index of tileset to use for this level in the Engines tileset register.
		indexOfTileset = -1;
		for (size_t i = 0; i < engine->tilesetRegister.size(); i++) {
			if (engine->tilesetRegister[i].name == nameOfTilest) {
				indexOfTileset = i;
			}
		}
		// If the wanted one wasn't found, use the default.
		if (indexOfTileset == -1) {
			indexOfTileset = 0;
		}

		// Populate the tilemap.
		for (int y = 0; y < tileGridSize.y; y++) {
			for (int x = 0; x < tileGridSize.x; x++) {
				int index = y * tileGridSize.x + x;
				tileMap.push_back(new Tile(*engine, engine->modelRegister[0], *engine->tilesetRegister[indexOfTileset].tileList[rawMapData[index]].texture, "", (engine->tilesetRegister[indexOfTileset].tileList[rawMapData[index]]).sourceFramePosition, glm::vec3(x * engine->tileSize.x, y * engine->tileSize.y, -0.01f), (engine->tilesetRegister[indexOfTileset].tileList[3]).sourceFrameSize));
			}
		}

	}
}