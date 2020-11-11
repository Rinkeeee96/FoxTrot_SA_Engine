#include "LevelBuilder.h"

void LevelBuilder::create() {
	engine.insertScene(bLevel);
	level = unique_ptr<Level>(bLevel);
}

void LevelBuilder::createLevel(nlohmann::json json) {
	for (auto& [key, value] : json.items()) {
		if (key == "properties") {
			for (auto& [propertyKey, propertyValue] : value.items())
			{
				if (propertyValue["name"] == "music") {
					string music = propertyValue["value"];
					map<string, string> sound = {
						{"Leve_Sound", "Assets/Sound/" + music},
					};
					bLevel->setSound(sound);
				}
			}
		}
		if (key == "width") {
			bLevel->setWidth(value);
		}
		if (key == "height") {
			bLevel->setHeight(value);
		}
	}
}

void LevelBuilder::createEntities(nlohmann::json layerValue, int id) {
	for (auto& [objectKey, objectValue] : layerValue["objects"].items())
	{
		ICharacter* object = nullptr;
		for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
		{
			if (objectPropertyValue["name"] == "type") {
				if (objectPropertyValue["value"] == "player") {
					object = new Player(id++);

					object->registerSprite(SpriteState::DEFAULT, this->playerDefault);
					object->registerSprite(SpriteState::AIR_ATTACK, this->playerAirAttack);
					object->registerSprite(SpriteState::RUN_RIGHT, this->playerRunRight);
					object->registerSprite(SpriteState::SLIDE, this->playerSlide);
					object->registerSprite(SpriteState::AIR_FALL_LEFT, this->playerFallLeft);
					object->registerSprite(SpriteState::AIR_JUMP_LEFT, this->playerJumpLeft);
					object->registerSprite(SpriteState::AIR_FALL_RIGHT, this->playerFallRight);
					object->registerSprite(SpriteState::AIR_JUMP_RIGHT, this->playerJumpRight);
					object->registerSprite(SpriteState::RUN_LEFT, this->playerRunLeft);
					object->changeToState(SpriteState::DEFAULT);
				}
				else if (objectPropertyValue["value"] == "slime") {
					object = new Slime(id++);
					object->registerSprite(SpriteState::DEFAULT, this->slimeDefault);
					object->changeToState(SpriteState::DEFAULT);
				}
				else {
					throw std::exception("invalid type");
				}
			}
		}

		object->setName(objectValue["name"]);
		object->setHeight(objectValue["height"]);
		object->setWidth(objectValue["width"]);
		object->setRotation(objectValue["rotation"]);
		object->setPositionX(objectValue["x"]);
		object->setPositionY(objectValue["y"]);
		object->setStatic(false);

		for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
		{
			if (objectPropertyValue["name"] == "density") {
				int densityString = objectPropertyValue["value"];
				object->setDensity(densityString);
			}
			if (objectPropertyValue["name"] == "friction") {
				int frictionString = objectPropertyValue["value"];
				object->setFriction(frictionString);
			}
			if (objectPropertyValue["name"] == "jump_height") {
				string jump_heightString = objectPropertyValue["value"];
				object->setJumpHeight(stringToFloat(jump_heightString));
			}
			if (objectPropertyValue["name"] == "restitution") {
				int restitutionString = objectPropertyValue["value"];
				object->setRestitution(restitutionString);
			}
			if (objectPropertyValue["name"] == "speed") {
				string speedString = objectPropertyValue["value"];
				object->setSpeed(stringToFloat(speedString));
			}
			if (objectPropertyValue["name"] == "health") {
				string healthString = objectPropertyValue["value"];
				object->setHealth(std::stoi(healthString));
			}
		}
		bLevel->addNewObjectToLayer(3, object);
	}
}

void LevelBuilder::createBackground(nlohmann::json layerValue, int id) {
	// TODO
}

void LevelBuilder::createTiles(nlohmann::json layerValue, int id) {
	// TODO
	int tileNum = 1;
	int currentX = 0;
	int currentY = 0;
	int tileAmount = layerValue["data"].size();
	for (int tileId : layerValue["data"]) {
		tileNum++;

		if (tileId != 0) {
			IGround* tile = new BaseGround(id++);

			// TODO get width and height from json
			tile->setWidth(16);
			tile->setHeight(16);
			tile->setStatic(true);
			tile->setPositionX(currentX * 16);
			tile->setPositionY(currentY * 16);

			SpriteObject* tileSprite = nullptr;

			if (spriteMap.find(tileId) == spriteMap.end()) {
				tileSprite = new SpriteObject(tileNum + 300, 16, 16, 1, 300, textureMap[tileId].c_str());
				engine.loadSprite(*tileSprite);
			}
			else {
				tileSprite = spriteMap[tileId];
			}

			tile->registerSprite(SpriteState::DEFAULT, tileSprite);
			tile->changeToState(SpriteState::DEFAULT);

			bLevel->addNewObjectToLayer(1, tile);
		}

		if (currentX == (layerValue["width"] - 1)) {
			currentY++;
			currentX = 0;
			continue;
		}
		currentX++;
	}
}

void LevelBuilder::loadTileSets(nlohmann::json json) {
	for (auto& [key, value] : json.items()) {
		// Tiles
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

							const string& spriteSource = spriteValue["image"];
							const string& spriteFilename = std::filesystem::path(spriteSource).filename().string();
							const string& spritePath = TILE_IMAGE_PATH + spriteFilename;

							textureMap.insert(pair<int, string>(currentGid, spritePath));
							currentGid++;
						}
					}
				}
			}
		}
	}
}

void LevelBuilder::loadSprites() {
	this->tileTop = new SpriteObject(1, 16, 16, 1, 150, "Assets/Sprites/World/LIGHT TILE WITHOUT TOP.png");
	this->playerDefault = new SpriteObject(100, 37, 50, 1, 150, "Assets/Sprites/Character/adventure.png");
	this->playerAirAttack = new SpriteObject(101, 37, 50, 4, 300, "Assets/Sprites/Character/adventure_air_attack1.png");
	this->playerRunRight = new SpriteObject(102, 37, 50, 6, 150, "Assets/Sprites/Character/adventure_run_right.png");
	this->playerSlide = new SpriteObject(103, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_slide.png");
	this->playerFallLeft = new SpriteObject(104, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_left.png");
	this->playerFallRight = new SpriteObject(107, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_fall_right.png");
	this->playerJumpLeft = new SpriteObject(105, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_left.png");
	this->playerRunLeft = new SpriteObject(106, 37, 50, 6, 150, "Assets/Sprites/Character/adventure_run_left.png");
	this->playerJumpRight = new SpriteObject(108, 37, 50, 2, 300, "Assets/Sprites/Character/adventure_jump_right.png");
	this->slimeDefault = new SpriteObject(109, 37, 50, 1, 150, "Assets/Levels/Tiles/slime_blue.png");

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
}