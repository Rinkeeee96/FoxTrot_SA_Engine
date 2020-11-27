#include "pch.h"
#include "SceneStateMachine.h"


SceneStateMachine::SceneStateMachine(Engine& _engine) : engine(_engine)
{
	factory = new SceneFactory();
	// Somehow delete this after they are used;
	CreatorImpl <MainMenu>* Menu = new CreatorImpl <MainMenu>();
	Menu->registerClass("MainMenu",factory);

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
}

SceneStateMachine::~SceneStateMachine()
{
	delete factory;
}

void SceneStateMachine::switchToScene(string identifier, const bool _useTransitionScreen)
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
	if (identifier.find("level") != string::npos) handlingLevel = true;

	shared_ptr<Scene> newScene = nullptr;

	if (!handlingLevel)
	{
		newScene = factory->create(identifier, sceneId++);
	}
	else
	{
		LoadLevelFacade levelLoader{ engine };
		LevelBuilder levelOneBuilder{ engine, sceneId++ };

		int levelToBuild = stoi(identifier.substr(6));
		cout << "Level to build: " << levelToBuild << endl;

		string path;
		path = "Assets/Levels/Maps/Level" + to_string(levelToBuild) + ".json";
		cout << "Path: " << path << endl;
		levelLoader.load(path, &levelOneBuilder);
		newScene = levelOneBuilder.getLevel();
	}

	if (sceneId > 10) sceneId = 1;
	if (newScene == nullptr) throw exception("NewScene is Nullptr so cant set new scene");

	engine.insertScene(newScene.get());
	engine.setCurrentScene(newScene->getSceneID());

	// Detach and delete the old now inactive scene
	if (currentScene != nullptr)
	{
		currentScene->onDetach();
		engine.deregisterScene(currentScene->getSceneID());
		currentScene = nullptr;
	}

	currentScene = newScene;

	// Handle some scene specific things
	if (currentScene && dynamic_cast<GeneralTransition*>(currentScene.get()))
	{
		((GeneralTransition*)currentScene.get())->setNextScene(transition);
	}

	if (currentScene && dynamic_cast<GameScene*>(currentScene.get()))
	{
		((GameScene*)currentScene.get())->registerStateMachine(this);
	}

	cout << "Setting current Scene to: " << typeid(*(engine.getCurrentScene())).name() << endl;

	currentScene->onAttach();
	currentScene->start();

}