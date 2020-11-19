#include "pch.h"
#include "LevelBuilder.h"

LevelBuilder::LevelBuilder(Engine& _engine, int levelId) : AbstractLevelBuilder(_engine), bLevel(new Level(levelId, 0, 0)) {
	
}

void LevelBuilder::create() {
	level = unique_ptr<Level>(bLevel);
}

// @brief 
/// Creates triggers objects and adds the triggers to the level
/// @param json 
void LevelBuilder::createTriggers(nlohmann::json layerValue) {
	for (auto& [objectKey, objectValue] : layerValue["objects"].items())
	{
		BaseTrigger* object = nullptr;
		for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
		{
			if (objectPropertyValue["name"] == "type") {
				string type = objectPropertyValue["value"];
				object = triggerFactory.create(type, id++);
			}
		}

		object->setHeight(objectValue["height"]);
		object->setWidth(objectValue["width"]);
		object->setPositionX(objectValue["x"]);
		object->setPositionY(objectValue["y"] + object->getHeight());
		object->setStatic(false);

		bLevel->addNewObjectToLayer(ENTITY_LAYER_INDEX, object);
	}
}

// @brief 
/// Creates level scene
/// @param json 
void LevelBuilder::createLevel(nlohmann::json json) {
	for (auto& [key, value] : json.items()) {
		if (key == "properties") {
			for (auto& [propertyKey, propertyValue] : value.items())
			{
				if (propertyValue["name"] == "music") {
					string music = propertyValue["value"];
					map<string, string> sound = {
						{"Level_Sound", "Assets/Sound/" + music},
					};
					bLevel->setSound(sound);
				}
			}
		}
		else if (key == "width") {
			bLevel->setSceneWidth(value);
		}
		else if (key == "height") {
			bLevel->setSceneHeight(value);
		}
		else if (key == "tilewidth") {
			this->mapTileWidth = value;

		}
		else if (key == "tileheight") {
			this->mapTileHeight = value;
		}
	}
	bLevel->setSceneWidth(bLevel->getSceneWidth() * this->mapTileWidth);
	bLevel->setSceneHeight(bLevel->getSceneHeight() * this->mapTileHeight);

	this->triggerFactory.registerTrigger("death", new DeathTrigger());
	this->triggerFactory.registerTrigger("win", new WinTrigger(*bLevel));
	characterFactory = std::make_unique<CharacterFactory>(engine, *bLevel);
	characterFactory = std::make_unique<CharacterFactory>(engine, *bLevel);
	this->initFactory();
}

// @brief 
/// Creates entities objects and adds the entities to the level
/// @param json 
void LevelBuilder::createEntities(nlohmann::json layerValue) {
	vector<ICharacter*> temp;
	for (auto& [objectKey, objectValue] : layerValue["objects"].items())
	{
		ICharacter* object = nullptr;
		for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
		{
			if (objectPropertyValue["name"] == "type") {
				object = characterFactory->create(objectPropertyValue["value"], id++);
			}
		}

		object->setHeight(objectValue["height"]);
		object->setWidth(objectValue["width"]);
		object->setRotation(objectValue["rotation"]);
		object->setPositionX(objectValue["x"]);
		object->setPositionY(objectValue["y"] + object->getHeight());
		object->setStatic(false);

		for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
		{
			if (objectPropertyValue["name"] == "density") {
				int densityString = objectPropertyValue["value"];
				object->setDensity(densityString);
			}
			else if (objectPropertyValue["name"] == "friction") {
				int frictionString = objectPropertyValue["value"];
				object->setFriction(frictionString);
			}
			else if (objectPropertyValue["name"] == "jump_height") {
				int jump_heightString = objectPropertyValue["value"];
				object->setJumpHeight(jump_heightString);
			}
			else if (objectPropertyValue["name"] == "restitution") {
				int restitutionString = objectPropertyValue["value"];
				object->setRestitution(restitutionString);
			}
			else if (objectPropertyValue["name"] == "speed") {
				int speedString = objectPropertyValue["value"];
				object->setSpeed(speedString);
			}
			else if (objectPropertyValue["name"] == "health") {
				int healthString = objectPropertyValue["value"];
				object->setHealth(healthString);
			}
		}
		bLevel->addNewObjectToLayer(ENTITY_LAYER_INDEX, object);
		temp.push_back(object);
	}
	//for (size_t i = 0; i < temp.size(); i++)
	//{
	//	if (Player* _player = dynamic_cast<Player*>(temp[i])) {
	//		for (size_t j = 0; j < temp.size(); j++)
	//		{
	//			if (IEnemy* _enemy = dynamic_cast<IEnemy*>(temp[j])) {
	//				_enemy->setPlayer(_player);
	//			}
	//		}
	//	}
	//}
}

// @brief 
/// Creates background objects and background the tiles to the level
/// @param json 
void LevelBuilder::createBackground(nlohmann::json layerValue) {
	for (auto& [objectKey, objectValue] : layerValue["objects"].items())
	{
		IGround* tile = new BaseGround(id++);

		int gid = objectValue["gid"];
		int width = objectValue["width"];
		int height = objectValue["height"];
		int x = objectValue["x"];
		int y = objectValue["y"];

		TileSprite* sprite = textureMap[gid];
		SpriteObject* tileSprite = new SpriteObject(currentTileId++, sprite->height, sprite->width, 1, 300, sprite->path.c_str());
		engine.loadSprite(*tileSprite);

		tile->setWidth(width);
		tile->setHeight(height);
		tile->setStatic(true);
		tile->setPositionX(x);
		tile->setPositionY(y);

		tile->registerSprite(SpriteState::DEFAULT, tileSprite);
		tile->changeToState(SpriteState::DEFAULT);

		bLevel->addNewObjectToLayer(BACKGROUND_LAYER_INDEX, tile, false);
	}
}

// @brief 
/// Creates decoration objects and adds the decoration to the level
/// @param json 
void LevelBuilder::createDecoration(nlohmann::json layerValue)
{
	int currentX = 0;
	int currentY = 0;
	int tileAmount = layerValue["data"].size();
	for (int tileId : layerValue["data"]) {

		if (tileId != 0) {
			IGround* tile = new BaseGround(id++);

			SpriteObject* tileSprite = nullptr;
			TileSprite* sprite = nullptr;

			if (spriteMap.find(tileId) == spriteMap.end()) {
				sprite = textureMap[tileId];
				tileSprite = new SpriteObject(currentTileId++, sprite->height, sprite->width, 1, 300, sprite->path.c_str());
				engine.loadSprite(*tileSprite);
			}
			else {
				tileSprite = spriteMap[tileId];
			}

			tile->setWidth(sprite->width);
			tile->setHeight(sprite->height);
			tile->setStatic(true);
			tile->setPositionX(currentX * mapTileWidth);
			tile->setPositionY((currentY * mapTileHeight) + mapTileHeight);

			tile->registerSprite(SpriteState::DEFAULT, tileSprite);
			tile->changeToState(SpriteState::DEFAULT);

			bLevel->addNewObjectToLayer(DECORATION_LAYER_INDEX, tile, false);
		}

		if (currentX == (layerValue["width"] - 1)) {
			currentY++;
			currentX = 0;
			continue;
		}
		currentX++;
	}
}

// @brief 
/// Creates particle objects and adds the particle to the level
/// @param json 
void LevelBuilder::createParticle(nlohmann::json layerValue)
{
	for (auto& [objectKey, objectValue] : layerValue["objects"].items())
	{
		ICharacter* object = nullptr;
		for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
		{
			if (objectPropertyValue["name"] == "type") {
					SpriteObject* particle1Sprite = new SpriteObject(currentTileId++, 20, 20, 5, 300, "Assets/Particles/fire.png");
					engine.loadSprite(*particle1Sprite);

					int type = objectPropertyValue["value"];

					ParticleAdapter* part = new ParticleAdapter(id++);
					part->registerSprite(SpriteState::DEFAULT, particle1Sprite);
					part->changeToState(SpriteState::DEFAULT);
					part->setPositionX(objectValue["x"]);
					part->setPositionY(objectValue["y"] + particle1Sprite->getHeight());
					part->setStyle((ParticleInit::ParticleStyle)type);
					bLevel->addNewObjectToLayer(PARTICLE_LAYER_INDEX, part);
				}
			else {
				throw std::exception(GAME_ERRORCODES[INVALID_TYPE]);
			}
		}
	}
}

// @brief 
/// Creates tile objects and adds the tiles to the level
/// @param json 
void LevelBuilder::createTiles(nlohmann::json layerValue) {
	int currentX = 0;
	int currentY = 0;
	int tileAmount = layerValue["data"].size();
	for (int tileId : layerValue["data"]) {

		if (tileId != 0) {
			IGround* tile = new BaseGround(id++);

			SpriteObject* tileSprite = nullptr;
			TileSprite* sprite = nullptr;

			if (spriteMap.find(tileId) == spriteMap.end()) {
				sprite = textureMap[tileId];
				tileSprite = new SpriteObject(currentTileId, sprite->height, sprite->width, 1, 300, sprite->path.c_str());
				currentTileId++;
				engine.loadSprite(*tileSprite);
			}
			else {
				tileSprite = spriteMap[tileId];
			}

			tile->setWidth(sprite->width);
			tile->setHeight(sprite->height);
			tile->setStatic(true);
			tile->setPositionX(currentX * mapTileWidth);
			tile->setPositionY((currentY * mapTileHeight) + sprite->height);

			tile->registerSprite(SpriteState::DEFAULT, tileSprite);
			tile->changeToState(SpriteState::DEFAULT);

			bLevel->addNewObjectToLayer(GROUND_LAYER_INDEX, tile);
		}

		if (currentX == (layerValue["width"] - 1)) {
			currentY++;
			currentX = 0;
			continue;
		}
		currentX++;
	}
}

// @brief 
/// Loads the tile set
/// @param json 
void LevelBuilder::loadTileSets(nlohmann::json json) {
	for (auto& [key, value] : json.items()) {
		if (key == "tilesets") {
			for (auto& [tileKey, tileValue] : value.items()) {
				int currentGid = tileValue["firstgid"];
				const string& source = tileValue["source"];
				const string& filename = std::filesystem::path(source).filename().string();
				const string& tilesetPath = TILESET_PATH + filename;

				auto tilesetFileStream = fileLoader.readFile(tilesetPath);
				nlohmann::json tilesetJson;
				tilesetFileStream >> tilesetJson;
				tilesetFileStream.close();

				for (auto& [tilesetKey, tilesetValue] : tilesetJson.items()) {
					if (tilesetKey == "tiles") {
						for (auto& [spriteKey, spriteValue] : tilesetValue.items()) {

							const string spriteSource = spriteValue["image"];
							const int spriteWidth = spriteValue["imagewidth"];
							const int spriteHeight = spriteValue["imageheight"];
							const string spriteFilename = std::filesystem::path(spriteSource).filename().string();
							const string spritePath = TILE_IMAGE_PATH + spriteFilename;

							TileSprite* currentTile = new TileSprite(spritePath, spriteWidth, spriteHeight);

							textureMap.insert(pair<int, TileSprite*>(currentGid, currentTile));
							currentGid++;
						}
					}
				}
			}
		}
	}
}

// @brief 
/// Creates the characterfactory and registers sprites by the object, cant be done within Tiled
void LevelBuilder::initFactory() {
	auto tileTop = new SpriteObject(textureId++, 16, 16, 1, 300, "Assets/Sprites/World/LIGHT TILE WITHOUT TOP.png");
	auto playerDefault = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 1, 150, "Assets/Sprites/Character/adventure.png");
	auto playerAirAttack = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 4, 300, "Assets/Sprites/Character/adventure_air_attack1.png");
	auto playerRunRight = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 6, 150, "Assets/Sprites/Character/adventure_run_right.png");
	auto playerSlide = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_slide.png");
	auto playerFallLeft = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_fall_left.png");
	auto playerFallRight = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_fall_right.png");
	auto playerJumpLeft = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_jump_left.png");
	auto playerRunLeft = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 6, 150, "Assets/Sprites/Character/adventure_run_left.png");
	auto playerJumpRight = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 2, 300, "Assets/Sprites/Character/adventure_jump_right.png");
	auto slimeDefault = new SpriteObject(textureId++, ICHARACTER_HEIGHT, ICHARACTER_WIDTH, 1, 150, "Assets/Levels/Tiles/slime_blue.png");

	engine.loadSprite(*tileTop);
	engine.loadSprite(*playerDefault);
	engine.loadSprite(*playerAirAttack);
	engine.loadSprite(*playerRunRight);
	engine.loadSprite(*playerSlide);
	engine.loadSprite(*playerFallLeft);
	engine.loadSprite(*playerFallRight);
	engine.loadSprite(*playerJumpLeft);
	engine.loadSprite(*playerRunLeft);
	engine.loadSprite(*playerJumpRight);
	engine.loadSprite(*slimeDefault);

	std::map<SpriteState, SpriteObject*> playerMap;
	playerMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::DEFAULT, playerDefault));
	playerMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_ATTACK, playerAirAttack));
	playerMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::RUN_RIGHT, playerRunRight));
	playerMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::SLIDE, playerSlide));
	playerMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_FALL_LEFT, playerFallLeft));
	playerMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_JUMP_LEFT, playerJumpLeft));
	playerMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_FALL_RIGHT, playerFallRight));
	playerMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::AIR_JUMP_RIGHT, playerJumpRight));
	playerMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::RUN_LEFT, playerRunLeft));
	characterFactory->registerCharacter("player", new Player(), playerMap);

	std::map<SpriteState, SpriteObject*> slimeMap;
	slimeMap.insert(std::pair<SpriteState, SpriteObject*>(SpriteState::DEFAULT, slimeDefault));
	characterFactory->registerCharacter("slime", new Slime(), slimeMap);

	std::map<std::string, std::map<SpriteState, SpriteObject*>> spriteObjectMap;
}