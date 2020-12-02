#include "pch.h"
#include "SceneStateMachine.h"

SceneStateMachine::SceneStateMachine(Engine& _engine) : engine(_engine)
{
	factory = shared_ptr<SceneFactory>(new  SceneFactory());
	// Somehow delete this after they are used;
	CreatorImpl <MainMenu>* Menu = new CreatorImpl<MainMenu>();
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
	if (identifier.find("Level") != string::npos) handlingLevel = true;

	std::unique_ptr<Scene> newScene = nullptr;

	if (!handlingLevel)
	{
		newScene = factory->create(identifier, sceneId++, engine, *this);
	}
	else
	{
		LoadLevelFacade levelLoader{ engine };

		int levelToBuild = stoi(identifier.substr(6));
		cout << "Level to build: " << levelToBuild << endl;

		LevelBuilder levelOneBuilder{ engine, sceneId++, *this };

		string path;
		path = "Assets/Levels/Maps/Level" + to_string(levelToBuild) + ".json";
		levelLoader.load(path, &levelOneBuilder);
		newScene = levelOneBuilder.getLevel();

		this->currentLevelIdentifier = identifier;
	}

	if (sceneId > 10) sceneId = 1;
	if (newScene == nullptr) throw exception("NewScene is Nullptr so cant set new scene");

	// Detach and delete the old now inactive scene
	if (currentScene != nullptr)
	{
		engine.deregisterScene(currentScene->getSceneID());
	}
	currentScene = std::move(newScene);

	engine.insertScene(currentScene.get());
	engine.setCurrentScene(currentScene->getSceneID());


	// Handle some scene specific things
	if (currentScene && dynamic_cast<GeneralTransition*>(currentScene.get()))
		((GeneralTransition*)currentScene.get())->setNextScene(transition);
	
	cout << "Setting current Scene to: " << typeid(*(engine.getCurrentScene())).name() << endl;

	currentScene->start();

}

string& SceneStateMachine::getCurrentLevelIdentifier()
{
	return this->currentLevelIdentifier;
}
