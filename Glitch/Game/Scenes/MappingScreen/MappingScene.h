#pragma once
#include "Game/Scenes/GameScene.h"
#include "Game/Commands/GameKeypressInvoker.h"

class MappingScene : public GameScene
{
public:
	MappingScene(const int id, unique_ptr<Engine>& engine, shared_ptr<SceneStateMachine> _statemachine) : GameScene(id, engine, _statemachine) {
		invoker = (GameKeypressInvoker*)engine->getKeypressedInvoker();
	};
	~MappingScene() {};

	void onAttach() override;
	void onDetach() override;
	void start(bool playSound) override;
	virtual void onUpdate(float deltaTime) override;

private:
	int textId = -1;
	float listStartX = 200;
	float listStartY = 400;
	int blockId = 1;

	void loadBackground();
	void loadMusic();
	void loadButtons();
	void loadSaveGame();

	void parseKeycodeList(unordered_map<KeyCode, string> parseList, const string& header);
	GameKeypressInvoker* invoker = nullptr;

	void createButtons();

	function<void(void)> onGodModeBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	function<void(void)> onJumpBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	function<void(void)> onMoveLeftBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	function<void(void)> onMoveRightBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	function<void(void)> onInventoryBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	function<void(void)> onPauseBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	function<void(void)> onStopBtnClick = [this]() {
		moveToNextScene = true;
		nextScene = "MainMenu";
	};

	unordered_map<KeyCode, string> keycodeStringMap = {
			{KeyCode::KEY_UNKNOWN, "Unknown"},
			{KeyCode::KEY_A, "A"},
			{KeyCode::KEY_B, "B"},
			{KeyCode::KEY_C, "C"},
			{KeyCode::KEY_D, "D"},
			{KeyCode::KEY_E, "E"},
			{KeyCode::KEY_F, "F"},
			{KeyCode::KEY_G, "G"},
			{KeyCode::KEY_H, "H"},
			{KeyCode::KEY_I, "I"},
			{KeyCode::KEY_J, "J"},
			{KeyCode::KEY_K, "K"},
			{KeyCode::KEY_L, "L"},
			{KeyCode::KEY_M, "M"},
			{KeyCode::KEY_N, "N"},
			{KeyCode::KEY_O, "O"},
			{KeyCode::KEY_P, "P"},
			{KeyCode::KEY_Q, "Q"},
			{KeyCode::KEY_R, "R"},
			{KeyCode::KEY_S, "S"},
			{KeyCode::KEY_T, "T"},
			{KeyCode::KEY_U, "U"},
			{KeyCode::KEY_V, "V"},
			{KeyCode::KEY_W, "W"},
			{KeyCode::KEY_X, "X"},
			{KeyCode::KEY_Y, "Y"},
			{KeyCode::KEY_Z, "Z"},
			{KeyCode::KEY_1, "1"},
			{KeyCode::KEY_2, "2"},
			{KeyCode::KEY_3, "3"},
			{KeyCode::KEY_4, "4"},
			{KeyCode::KEY_5, "5"},
			{KeyCode::KEY_6, "6"},
			{KeyCode::KEY_7, "7"},
			{KeyCode::KEY_8, "8"},
			{KeyCode::KEY_9, "9"},
			{KeyCode::KEY_0, "0"},
			{KeyCode::KEY_RETURN, "Return"},
			{KeyCode::KEY_ESCAPE, "Esc"},
			{KeyCode::KEY_BACKSPACE, "Backspace"},
			{KeyCode::KEY_TAB, "Tab"},
			{KeyCode::KEY_SPACE, "Space"},
			{KeyCode::KEY_MINUS, "-"},
			{KeyCode::KEY_EQUALS, "+"},
			{KeyCode::KEY_LEFTBRACKET, "("},
			{KeyCode::KEY_RIGHTBRACKET, ")"},
			{KeyCode::KEY_BACKSLASH, "/"},
			{KeyCode::KEY_SEMICOLON, ";"},
			{KeyCode::KEY_APOSTROPHE, "'"},
			{KeyCode::KEY_GRAVE, ""},
			{KeyCode::KEY_COMMA, ","},
			{KeyCode::KEY_PERIOD, "."},
			{KeyCode::KEY_SLASH, "\\"},
			{KeyCode::KEY_CAPSLOCK, "CAPS"},
			{KeyCode::KEY_F1, "F1"},
			{KeyCode::KEY_F2, "F2"},
			{KeyCode::KEY_F3, "F3"},
			{KeyCode::KEY_F4, "F4"},
			{KeyCode::KEY_F5, "F5"},
			{KeyCode::KEY_F6, "F6"},
			{KeyCode::KEY_F7, "F7"},
			{KeyCode::KEY_F8, "F8"},
			{KeyCode::KEY_F9, "F9"},
			{KeyCode::KEY_F10, "F10"},
			{KeyCode::KEY_F11, "F11"},
			{KeyCode::KEY_F12, "F12"},

			{KeyCode::KEY_PRINTSCREEN, "PrntScr"},
			{KeyCode::KEY_SCROLLLOCK, "ScrlLck"},
			{KeyCode::KEY_PAUSE, "Pause"},
			{KeyCode::KEY_INSERT, "Insert"},
			{KeyCode::KEY_HOME, "Home"},
			{KeyCode::KEY_PAGEUP, "PgUp"},
			{KeyCode::KEY_DELETE, "Del"},
			{KeyCode::KEY_END, "End"},
			{KeyCode::KEY_PAGEDOWN, "PgDwn"},
			{KeyCode::KEY_RIGHT, "Right"},
			{KeyCode::KEY_LEFT, "Left"},
			{KeyCode::KEY_DOWN, "Down"},
			{KeyCode::KEY_UP, "Up"},
			{KeyCode::KEY_KP_LEFTPAREN, "{"},
			{KeyCode::KEY_KP_RIGHTPAREN, "}"},
			{KeyCode::KEY_KP_LEFTBRACE, "["},
			{KeyCode::KEY_KP_RIGHTBRACE, "]"},
			{KeyCode::KEY_KP_BACKSPACE, "backspace"},
			{KeyCode::KEY_LCTRL, "Left ctrl"},
			{KeyCode::KEY_LSHIFT, "Right ctrl"},
			{KeyCode::KEY_LALT, "Left alt"},
			{KeyCode::KEY_LGUI, "Left windows"},
			{KeyCode::KEY_RCTRL, "Right ctrl"},
			{KeyCode::KEY_RSHIFT, "Right shift"},
			{KeyCode::KEY_RALT, "Left alt"},
			{KeyCode::KEY_RGUI, "Right windows"}
	};
};
