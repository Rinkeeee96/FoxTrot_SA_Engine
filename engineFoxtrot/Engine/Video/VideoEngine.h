#pragma once
#include "VideoFacade.h"
#include "Fps/FrameData.h"
#include "Structs/HelperStructs.h"
#include "Events/Action/FpsToggleEvent.h"
#include "SceneManager/Scene.h"
#include "ParticleSystem/ParticleAdapter.h"


#define NO_RED					0
#define NO_BLUE					0
#define NO_GREEN				0

#define OFFSETFIX				275

#define FPS_Y_POSITION_OFFSET	15

#define CAMERA_BOX_HEIGHT		350
#define CAMERA_BOX_WIDTH		350
#define CAMERA_BOX_X			785
#define CAMERA_BOX_Y			365

struct API Sprite
{
	int spriteID = 0;
	const char* filename = "";
};

/// @brief 
/// Video is the SDL2 wrapper

class API VideoEngine
{
public:
	VideoEngine();
	~VideoEngine();

	void clearScreen();
	void drawScreen();
	void loadImage(const SpriteObject& spriteObject);

	void renderCopy(Drawable& drawable);

	void updateScreen();

	void drawFps();
	void drawFps(double fps, int xPos, int yPos, const string& prefix);
	bool toggleFps(Event& fpsEvent);

	bool receiveTick(Event& tickEvent);

	bool drawParticle(ParticleAdapter* part);

	void calculateOffset(Object& obj, int sceneWidth, int sceneHeight);

	Scene** pointerToCurrentScene = nullptr;

	bool checkInScreen(Object* obj);

private:
	IVideoFacade* videoFacade = new VideoFacade;

	FrameData* frameData = nullptr;
	bool shouldDrawFps = false;
};
