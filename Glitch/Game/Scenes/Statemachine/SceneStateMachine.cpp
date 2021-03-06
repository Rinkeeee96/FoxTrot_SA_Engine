#include "pch.h"
#include "SceneStateMachine.h"
#include <Game/Scenes/Story/ChapterTwoScene.h>
#include <Game/Scenes/Story/ChapterThreeScene.h>
#include <Game/Scenes/GameInfo/GameInfo.h>

/// @brief Creates all scene states
/// @param _engine 
/// @param _savegame 
SceneStateMachine::SceneStateMachine(unique_ptr<Engine>& _engine, shared_ptr<Savegame> _savegame) : engine(_engine), savegame(_savegame)
{
	factory = shared_ptr<SceneFactory>(new  SceneFactory());
	// Somehow delete this after they are used;
	CreatorImpl <MainMenu>* Menu = new CreatorImpl<MainMenu>();
	Menu->registerClass("MainMenu", factory);

	CreatorImpl <DeathScreen>* Death = new CreatorImpl <DeathScreen>();
	Death->registerClass("DeathScreen", factory);

	CreatorImpl <Overworld>* overworld = new CreatorImpl <Overworld>();
	overworld->registerClass("Overworld", factory);

	CreatorImpl <SaveScreen>* saveScreen = new CreatorImpl <SaveScreen>();
	saveScreen->registerClass("SaveScreen", factory);

	CreatorImpl <GeneralTransition>* general = new CreatorImpl <GeneralTransition>();
	general->registerClass("GeneralTransition", factory);

	CreatorImpl <WinScreen>* win = new CreatorImpl <WinScreen>();
	win->registerClass("WinScreen", factory);

	CreatorImpl <CreditsScene>* cred = new CreatorImpl <CreditsScene>();
	cred->registerClass("CreditsSreen", factory);

	CreatorImpl <ChapterOneScene>* chap = new CreatorImpl <ChapterOneScene>();
	chap->registerClass("ChapterOne", factory);

	CreatorImpl <ChapterTwoScene>* chap2 = new CreatorImpl <ChapterTwoScene>();
	chap2->registerClass("ChapterTwo", factory);

	CreatorImpl <ChapterThreeScene>* chap3 = new CreatorImpl <ChapterThreeScene>();
	chap3->registerClass("ChapterThree", factory);

	CreatorImpl <Shop>* shop = new CreatorImpl <Shop>();
	shop->registerClass("Shop", factory);

	CreatorImpl <MappingScene>* mappingScreen = new CreatorImpl <MappingScene>();
	mappingScreen->registerClass("MappingScreen", factory);

	CreatorImpl <GameInfo>* infoScreen = new CreatorImpl <GameInfo>();
	infoScreen->registerClass("GameInfo", factory);
}

SceneStateMachine::~SceneStateMachine() {}

/// @brief Load level according to the identifier
/// @param identifier 
/// @return 
unique_ptr<Scene> SceneStateMachine::loadLevel(const string& identifier) {
	std::unique_ptr<Scene> newScene = nullptr;
	LoadLevelFacade levelLoader{ engine };

	levelToBuild = stoi(identifier.substr(6));
	if (DEBUG_MAIN) cout << "Level to build: " << levelToBuild << endl;

	LevelBuilder levelOneBuilder{ engine, sceneId++, shared_from_this()};

	string path;
	path = "Assets/Levels/Maps/Level" + to_string(levelToBuild) + ".json";
	levelLoader.load(path, &levelOneBuilder);
	newScene = levelOneBuilder.getLevel();

	this->currentLevelIdentifier = identifier;
	return newScene;
}

/// @brief Switch to the scene according the the identifier
/// @param identifier 
/// @param _useTransitionScreen 
/// @param playSound 
void SceneStateMachine::switchToScene(string identifier, const bool _useTransitionScreen, bool playSound)
{
	bool useTransitionScreen = _useTransitionScreen;
	if (DEBUG_MAIN) { useTransitionScreen = false; }

	string transition = "";
	if (useTransitionScreen)
	{
		transition = identifier;
		identifier = "GeneralTransition";
	}

	bool handlingLevel = false;
	if (identifier.find("Level") != string::npos) handlingLevel = true;

	std::unique_ptr<Scene> newScene = nullptr;

	if (!handlingLevel)
	{
		newScene = factory->create(identifier, sceneId++, engine, shared_from_this());
	}
	else
	{
		newScene = this->loadLevel(identifier);
	}

	if (sceneId > 10) sceneId = 1;
	if (newScene == nullptr) throw exception("SceneStateMachine: NewScene is Nullptr");

	// Detach and delete the old now inactive scene
	if (currentSceneId != -1)
	{
		engine->deregisterCurrentScene();
	}

	if (dynamic_cast<GameScene*>(newScene.get()))
		((GameScene*)newScene.get())->registerSavegame(savegame);

	// Handle some scene specific things
	if (dynamic_cast<GeneralTransition*>(newScene.get()))
		((GeneralTransition*)newScene.get())->setNextScene(transition);

	currentSceneId = newScene->getSceneID();

	activePopups.clear();

	engine->insertScene(std::move(newScene));
	engine->setCurrentScene(currentSceneId);

	engine->startCurrentScene(playSound);


}

/// @brief Returns currentLevelIdentifier
/// @return 
string& SceneStateMachine::getCurrentLevelIdentifier()
{
	return this->currentLevelIdentifier;
}