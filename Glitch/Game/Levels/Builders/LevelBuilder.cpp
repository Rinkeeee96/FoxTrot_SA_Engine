#include "pch.h"
#include "LevelBuilder.h"
#include "Game/Characters/Enemies/IEnemy.h"
#include "Game/Ground/IGround.h"
#include "Game/Ground/BaseGround.h"
#include "Game/Ground/SnowyGround.h"
#include "Game/Ground/BouncingGround.h"
#include "Game/Characters/Enemies/Slime.h"
#include "Game/Characters/Enemies/Skryo.h"
#include "Game/Characters/Enemies/SlimeBoss.h"
#include "Game/Factories/CharacterFactory.h"
#include <Game/Triggers/MusicTrigger.h>
#include <Game/Triggers/SpikeTrigger.h>

LevelBuilder::LevelBuilder(unique_ptr<Engine>& _engine, int levelId, shared_ptr<SceneStateMachine> _statemachine)
	: AbstractLevelBuilder(_engine), bLevel(new Level(levelId, 0, 0, _engine, _statemachine)) {}

/// @brief Gets the alwaysDraw objects from the json file
/// @param layerValue 
/// @return 
bool LevelBuilder::getAlwaysDrawFromJson(nlohmann::json layerValue)
{
	for (auto& [objectKey, objectValue] : layerValue["properties"].items()) {
		if (objectValue["name"] == "Always Draw") {
			bool type = objectValue["value"];
			return type;
		}
	}
	return false;
}

/// @brief Creates a unique pointer for a level
void LevelBuilder::create() {
	level = unique_ptr<Level>(bLevel);
}

// @brief 
/// Creates triggers objects and adds the triggers to the level
/// @param json 
void LevelBuilder::createTriggers(nlohmann::json layerValue) {
	bool alwaysDrawLayer = getAlwaysDrawFromJson(layerValue);
	for (auto& [objectKey, objectValue] : layerValue["objects"].items())
	{
		shared_ptr<BaseTrigger> object = nullptr;
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
		object->setStatic(true);

		bLevel->addNewObjectToLayer(ENTITY_LAYER_INDEX, object, true, alwaysDrawLayer);
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

	this->triggerFactory.registerTrigger("death", shared_ptr<DeathTrigger>(new DeathTrigger(bLevel->getEventDispatcher())));
	this->triggerFactory.registerTrigger("win", shared_ptr<WinTrigger>(new WinTrigger(*bLevel, bLevel->getEventDispatcher())));
	this->triggerFactory.registerTrigger("music", shared_ptr<MusicTrigger>(new MusicTrigger(*bLevel, bLevel->getEngine(), bLevel->getEventDispatcher())));
	this->triggerFactory.registerTrigger("spike", shared_ptr<SpikeTrigger>(new SpikeTrigger(bLevel->getEventDispatcher())));
	characterFactory = std::make_unique<CharacterFactory>(engine, *bLevel);
	this->initFactory();
}

// @brief 
/// Creates entities objects and adds the entities to the level
/// @param json 
void LevelBuilder::createEntities(nlohmann::json layerValue) {
	bool alwaysDrawLayer = getAlwaysDrawFromJson(layerValue);
	vector<shared_ptr<ICharacter>> temp;
	for (auto& [objectKey, objectValue] : layerValue["objects"].items())
	{
		shared_ptr<ICharacter> object = nullptr;
		for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
		{
			if (objectPropertyValue["name"] == "type") {
				object = characterFactory->create(objectPropertyValue["value"], id++);
			}
		}
		
		if (object == nullptr) throw exception("LevelBuilder: Object is nullptr");

		object->setHeight(objectValue["height"]);
		object->setWidth(objectValue["width"]);
		object->setRotation(objectValue["rotation"]);
		object->setPositionX(objectValue["x"]);
		object->setPositionY(objectValue["y"] + object->getHeight());
		object->setSpawnX(object->getPositionX());
		object->setSpawnY(object->getPositionY());
		object->setStatic(false);

		for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
		{
			if (objectPropertyValue["name"] == "density") {
				float densityString = objectPropertyValue["value"];
				object->setDensity(densityString);
			}
			else if (objectPropertyValue["name"] == "friction") {
				float frictionString = objectPropertyValue["value"];
				object->setFriction(frictionString);
			}
			else if (objectPropertyValue["name"] == "jump_height") {
				float jump_heightString = objectPropertyValue["value"];
				object->setJumpHeight(jump_heightString);
			}
			else if (objectPropertyValue["name"] == "restitution") {
				float restitutionString = objectPropertyValue["value"];
				object->setRestitution(restitutionString);
			}
			else if (objectPropertyValue["name"] == "speed") {
				float speedString = objectPropertyValue["value"];
				object->setSpeed(speedString);
			}
			else if (objectPropertyValue["name"] == "health") {
				int healthString = objectPropertyValue["value"];
				object->setTotalHealth(healthString);
				object->setCurrentHealth(healthString);
			}
		}
		bLevel->addNewObjectToLayer(ENTITY_LAYER_INDEX, object, true, alwaysDrawLayer);
		temp.push_back(object);
	}
	for (size_t i = 0; i < temp.size(); i++)
	{
		if (Player* _player = dynamic_cast<Player*>(temp[i].get())) {
			for (size_t j = 0; j < temp.size(); j++)
			{
				if (IEnemy* _enemy = dynamic_cast<IEnemy*>(temp[j].get())) {
					_enemy->setPlayer(&bLevel->getPlayer());
				}
			}
			break;
		}
	}
}

// @brief 
/// Creates background objects and background the tiles to the level
/// @param json 
void LevelBuilder::createBackground(nlohmann::json layerValue) {
	bool alwaysDrawLayer = getAlwaysDrawFromJson(layerValue);
	for (auto& [objectKey, objectValue] : layerValue["objects"].items())
	{
		shared_ptr<IGround> tile = shared_ptr<BaseGround>(new BaseGround(bLevel->getEventDispatcher(), id++));

		int gid = objectValue["gid"];
		float width = objectValue["width"];
		float height = objectValue["height"];
		float x = objectValue["x"];
		float y = objectValue["y"];

		TileSprite* sprite = textureMap[gid];
		shared_ptr<SpriteObject> tileSprite = shared_ptr<SpriteObject>(new SpriteObject(textureId++, sprite->height, sprite->width, 1, 300, sprite->path.c_str()));

		tile->setWidth(width);
		tile->setHeight(height);
		tile->setStatic(true);
		tile->setPositionX(x);
		tile->setPositionY(y);

		tile->registerSprite(SpriteState::DEFAULT, tileSprite);
		tile->changeToState(SpriteState::DEFAULT);

		bLevel->addNewObjectToLayer(BACKGROUND_LAYER_INDEX, tile, false, alwaysDrawLayer);
	}
}

// @brief 
/// Creates decoration objects and adds the decoration to the level
/// @param json 
void LevelBuilder::createDecoration(nlohmann::json layerValue)
{
	bool alwaysDrawLayer = getAlwaysDrawFromJson(layerValue);
	float currentX = 0;
	float currentY = 0;
	size_t tileAmount = layerValue["data"].size();
	for (int tileId : layerValue["data"]) {

		if (tileId != 0) {
			shared_ptr<IGround> tile = shared_ptr<BaseGround>(new BaseGround(bLevel->getEventDispatcher(), id++));

			shared_ptr<SpriteObject> tileSprite = nullptr;
			TileSprite* sprite = nullptr;

			if (spriteMap.find(tileId) == spriteMap.end()) {
				sprite = textureMap[tileId];
				tileSprite = make_unique<SpriteObject>(textureId++, sprite->height, sprite->width, 1, 300, sprite->path.c_str());
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

			bLevel->addNewObjectToLayer(DECORATION_LAYER_INDEX, tile, false, alwaysDrawLayer);
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
	bool alwaysDrawLayer = getAlwaysDrawFromJson(layerValue);
	for (auto& [objectKey, objectValue] : layerValue["objects"].items())
	{
		ICharacter* object = nullptr;
		for (auto& [objectPropertyKey, objectPropertyValue] : objectValue["properties"].items())
		{
			if (objectPropertyValue["name"] == "type") {
				shared_ptr<SpriteObject> particle1Sprite = shared_ptr<SpriteObject>(new SpriteObject(textureId++, 20, 20, 5, 300, "Assets/Particles/fire.png"));

				int type = objectPropertyValue["value"];

				shared_ptr<ParticleAdapter> part = shared_ptr<ParticleAdapter>(new ParticleAdapter(id++));
				part->registerSprite(SpriteState::DEFAULT, particle1Sprite);
				part->changeToState(SpriteState::DEFAULT);
				part->setPositionX(objectValue["x"]);
				part->setPositionY(objectValue["y"] + particle1Sprite->getHeight());
				part->setWidth(objectValue["width"]);
				part->setHeight(objectValue["height"]);
				part->setStyle((ParticleInit::ParticleStyle)type);


				bLevel->addNewObjectToLayer(PARTICLE_LAYER_INDEX, part, false, alwaysDrawLayer);
			}
			else {
				throw exception("LevelBuilder: Invalid Type");;
			}
		}
	}
}

// @brief 
/// Creates tile objects and adds the tiles to the level
/// @param json 
void LevelBuilder::createTiles(nlohmann::json layerValue) {
	bool alwaysDrawLayer = getAlwaysDrawFromJson(layerValue);
	int currentX = 0;
	int currentY = 0;
	size_t tileAmount = layerValue["data"].size();
	for (int tileId : layerValue["data"]) {

		if (tileId != 0) {
			shared_ptr<SpriteObject> tileSprite = nullptr;
			TileSprite* sprite = nullptr;

			if (spriteMap.find(tileId) == spriteMap.end()) {
				sprite = textureMap[tileId];
				tileSprite = shared_ptr<SpriteObject>(new SpriteObject(textureId++, sprite->height, sprite->width, 1, 300, sprite->path.c_str()));
				currentTileId++;
			}
			else {
				tileSprite = spriteMap[tileId];
			}

			shared_ptr<IGround> tile;

			if (sprite->properties.size() == 0) {
				tile = shared_ptr<BaseGround>(new BaseGround(bLevel->getEventDispatcher(), id++));
			}

			// TODO Factory
			for (auto [Key, Value] : sprite->properties) {
				if (Key == "type" && Value == "ice") {
					tile = shared_ptr<SnowyGround>(new SnowyGround(bLevel->getEventDispatcher(), id++));
				}
				if (Key == "type" && Value == "bounce") {
					tile = shared_ptr<BouncingGround>(new BouncingGround(*bLevel, bLevel->getEventDispatcher(), id++));
				}
			}

			tile->setWidth(sprite->width);
			tile->setHeight(sprite->height);
			tile->setStatic(true);
			tile->setPositionX(currentX * (float)mapTileWidth);
			tile->setPositionY((currentY * (float)mapTileHeight) + sprite->height);
			tile->registerSprite(SpriteState::DEFAULT, tileSprite);
			tile->changeToState(SpriteState::DEFAULT);

			bLevel->addNewObjectToLayer(GROUND_LAYER_INDEX, tile, true, alwaysDrawLayer);
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
							const float spriteWidth = spriteValue["imagewidth"];
							const float spriteHeight = spriteValue["imageheight"];
							const string spriteFilename = std::filesystem::path(spriteSource).filename().string();
							const string spritePath = TILE_IMAGE_PATH + spriteFilename;

							TileSprite* currentTile = new TileSprite(spritePath, spriteWidth, spriteHeight);

							for (auto& [Key, Value] : spriteValue["properties"].items()) {
								currentTile->properties.insert(pair<string, string>(Value["name"], Value["value"]));
							}

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
	auto tileTop = shared_ptr<SpriteObject>(new SpriteObject(textureId++, 16, 16, 1, 300, "Assets/Sprites/World/LIGHT TILE WITHOUT TOP.png"));

	characterFactory->registerCharacter("player", shared_ptr<Player>(new Player(bLevel->getEventDispatcher())), &textureId);

	characterFactory->registerCharacter("slime", shared_ptr<Slime>(new Slime(bLevel->getEventDispatcher())), &textureId);
	characterFactory->registerCharacter("iceslime", shared_ptr<Slime>(new Slime(bLevel->getEventDispatcher(), SlimeType::Ice)), &textureId);

	characterFactory->registerCharacter("fleye", shared_ptr<Fleye>(new Fleye(bLevel->getEventDispatcher())), &textureId);

	characterFactory->registerCharacter("jumpkin", shared_ptr<Jumpkin>(new Jumpkin(bLevel->getEventDispatcher())), &textureId);

	characterFactory->registerCharacter("skryo", shared_ptr<Skryo>(new Skryo(bLevel->getEventDispatcher())), &textureId);

	characterFactory->registerCharacter("slimeboss", shared_ptr<SlimeBoss>(new SlimeBoss(*bLevel, bLevel->getEventDispatcher())), &textureId);

	std::map<std::string, std::map<SpriteState, shared_ptr<SpriteObject>>> spriteObjectMap;
}