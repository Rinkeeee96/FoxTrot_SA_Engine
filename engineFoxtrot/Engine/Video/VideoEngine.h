#pragma once
#include "VideoFacade.h"
#include "Fps/FrameData.h"
#include "Structs/HelperStructs.h"
#include "SceneManager/Scene.h"
#include "ParticleSystem/ParticleAdapter.h"
#include "General/ISubsystem.h"

#define NO_RED					0
#define NO_BLUE					0
#define NO_GREEN				0

#define OFFSETFIX				275

#define FPS_Y_POSITION_OFFSET	15

#define CAMERA_BOX_HEIGHT		350
#define CAMERA_BOX_WIDTH		350
#define CAMERA_BOX_X			785
#define CAMERA_BOX_Y			365

#define FPS_MESSAGE_WIDTH 100
#define FPS_MESSAGE_HEIGHT 50


struct API Sprite
{
	int spriteID = 0;
	const char* filename = "";
};

/// @brief 
/// Video is the SDL2 wrapper

class API VideoEngine : public ISubsystem
{
public:
	VideoEngine(FrameData& _frameData);
	~VideoEngine();

	void loadImage(const SpriteObject& spriteObject);
	void renderCopy(Drawable& drawable);
	void toggleFps();
	bool drawParticle(ParticleAdapter* part);
	void calculateOffset(Object& obj, int sceneWidth, int sceneHeight);


	bool checkObjectInScreen(const Object& obj);

	void clearVideoEngine();

	void start(EventDispatcher& dispatcher) override;
	void update() override;
	void shutdown() override;

	Scene** pointerToCurrentScene = nullptr;
private:
	void drawFps();
	void drawFps(double fps, int xPos, int yPos, const string& prefix);
	void updateScreen();
	void clearScreen();
	void drawScreen();

	IVideoFacade* videoFacade = nullptr;
	
	FrameData& frameData;
	bool shouldDrawFps = false;
};
