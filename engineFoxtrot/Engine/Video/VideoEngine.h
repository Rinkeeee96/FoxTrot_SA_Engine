#pragma once
#include "VideoFacade.h"
#include "Fps/FrameData.h"
#include "Structs/HelperStructs.h"
#include "SceneManager/Scene.h"
#include "ParticleSystem/ParticleAdapter.h"
#include "General/ISubsystem.h"
#include "Events/Video/VideoZoomEvent.h"

#define NO_RED					0
#define NO_BLUE					0
#define NO_GREEN				0

#define OFFSETFIX				275

#define FPS_Y_POSITION_OFFSET	15

#define CAMERA_BOX_HEIGHT		350
#define CAMERA_BOX_WIDTH		350
#define CAMERA_BOX_X			785
#define CAMERA_BOX_Y			365

#define FPS_MESSAGE_WIDTH		100
#define FPS_MESSAGE_HEIGHT		50

#define BASE_SCALE				1

/// @brief 
/// VideoEngine is the SDL2 wrapper
class VideoEngine : public ISubsystem
{
public:
	API VideoEngine(unique_ptr<FrameData>& _frameData);
	API ~VideoEngine();

	API void loadImage(const shared_ptr<SpriteObject> spriteObject);
	API void renderCopy(shared_ptr<Drawable>);
	API void toggleFps();
	API void drawParticle(shared_ptr<ParticleAdapter> part);
	API void calculateOffset(shared_ptr<Object> obj, int sceneWidth, int sceneHeight);

	API bool checkObjectInScreen(const shared_ptr<Object> obj);

	API void clearVideoEngine();

	API void start(EventDispatcher& dispatcher) override;
	API void update() override;
	API void shutdown() override;

	API bool zoom(const Event& event);

	unique_ptr<Scene>* pointerToCurrentScene = nullptr;

	const IVideoFacade& getVideoFacade() const { return *this->videoFacade; }
private:
	void drawFps();
	void drawFps(double fps, int xPos, int yPos, const string& prefix);
	void updateScreen();
	void clearScreen();
	void drawScreen();

	unique_ptr<IVideoFacade> videoFacade = nullptr;
	
	unique_ptr<FrameData>& frameData;
	bool shouldDrawFps = false;
	float currentScale = BASE_SCALE;
};
