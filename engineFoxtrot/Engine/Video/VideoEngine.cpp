#include "stdafx.h"
#include "Events\AppTickEvent60.h"
#include "Events\EventSingleton.h"
#include "VideoEngine.h"

VideoEngine::VideoEngine()
{
	frameData = new FrameData;
	EventSingleton::get_instance().setEventCallback<AppTickEvent60>(BIND_EVENT_FN(VideoEngine::receiveTick));
	EventSingleton::get_instance().setEventCallback<FpsToggleEvent>(BIND_EVENT_FN(VideoEngine::toggleFps));
}

VideoEngine::~VideoEngine()
{
}

/// @brief 
/// Clears the SDL screen
void VideoEngine::clearScreen()
{
	videoFacade->clearScreen();
}

/// @brief 
/// Draws the SDL screen
void VideoEngine::drawScreen()
{
	videoFacade->drawScreen();
}

/// @brief Loads the PNG files AKA sprites
/// @param spriteID 
/// @param filename
void VideoEngine::loadImage(const SpriteObject& spriteObject)
{
	videoFacade->loadImage(spriteObject);
}

/// @brief Sets the sprite on the screen
/// @param Object 
void VideoEngine::renderCopy(Drawable& object) {
	videoFacade->renderCopy(object);
}

/// @brief 
/// Calculates the camera offset based on the player position.
/// @param obj 
/// This is the Object marked as a player
/// @param sceneWidth 
/// @param sceneHeight 
void VideoEngine::calculateOffset(Object& obj, int sceneWidth, int sceneHeight)
{
	
	// Place obj variables in temporary variables for easy use. 
	// Object Y pos needs to be subtracted with the height due to the position conversion from Object to SDL2.
	int objectPosY = (int)obj.getPositionY() - (int)obj.getHeight();
	int objectPosX = (int)obj.getPositionX();
	int objectWidth = (int)obj.getWidth();
	int objectHeight = (int)obj.getHeight();

	int cameraOffsetX = videoFacade->getXCameraOffset();
	int cameraOffsetY = videoFacade->getYCameraOffset();

	// Check if the player is located inside the camera view. If not continue and calculate the offsets
	if (objectPosX 					 <= cameraOffsetX + CAMERA_BOX_X &&
		objectPosX + objectWidth     >= cameraOffsetX + (CAMERA_BOX_X + CAMERA_BOX_WIDTH)  &&
		objectPosY					 <= cameraOffsetY + CAMERA_BOX_Y &&
		objectPosY + objectHeight    >= cameraOffsetY + (CAMERA_BOX_Y + CAMERA_BOX_HEIGHT))
	{
		return;
	}

	int newXOffset = 0;
	int newYOffset = 0;
	bool changedX = false;
	bool changedY = false;

	if (objectPosX + objectWidth >= cameraOffsetX + CAMERA_BOX_X + CAMERA_BOX_WIDTH)
	{
		newXOffset = objectPosX + objectWidth - (CAMERA_BOX_X + CAMERA_BOX_WIDTH);
		changedX = true;
	}
	else if (objectPosX <= cameraOffsetX + CAMERA_BOX_X)
	{
		newXOffset = objectPosX - CAMERA_BOX_X;
		changedX = true;
	}

	if (objectPosY + objectHeight >= cameraOffsetY + CAMERA_BOX_Y + CAMERA_BOX_HEIGHT)
	{
		newYOffset = objectPosY + objectHeight - (CAMERA_BOX_Y + CAMERA_BOX_HEIGHT);
		changedY = true;
	}
	else if (objectPosY <= cameraOffsetY + CAMERA_BOX_Y)
	{
		newYOffset = objectPosY - CAMERA_BOX_Y;
		changedY = true;
	}


	//// Check if we can actually move the camera due to the level sizes
	if (newYOffset > 0 && newYOffset + (CAMERA_BOX_Y *2) + CAMERA_BOX_HEIGHT < sceneHeight && changedY)
	{
		videoFacade->setYCameraOffset(newYOffset);
	}
	if (newXOffset > 0 && newXOffset + (CAMERA_BOX_X * 2) + CAMERA_BOX_WIDTH < sceneWidth && changedX)
	{
		videoFacade->setXCameraOffset(newXOffset);
	}
}

bool VideoEngine::checkInScreen(Object* obj) {
	if (obj->getPositionX() > videoFacade->getXCameraOffset() - DRAW_OFFSCREEN_BUFFER &&
		obj->getPositionX() < videoFacade->getXCameraOffset() + WINDOW_WIDTH &&
		obj->getPositionY() > videoFacade->getYCameraOffset() + DRAW_OFFSCREEN_BUFFER &&
		obj->getPositionY() < videoFacade->getYCameraOffset() + WINDOW_HEIGHT) {
		return true;
	}
	return false;;
}

bool VideoEngine::checkFixedLayers(Object* obj)
{
	for (auto layer : (*pointerToCurrentScene)->getLayers()) {
		if (layer.second->alwaysVisible) {
			for (auto object : (*pointerToCurrentScene)->getAllObjectsInLayer(layer.first)) {
				return object == obj;
			}
		}
	}
	
	return false;
}

/// @brief 
/// Update all the sprites on the screen
/// Updates the camera offset
void VideoEngine::updateScreen()
{
	if (pointerToCurrentScene == nullptr) return;
	//if (pointerToObjectVector->capacity() <= 0) return;
	if ((*pointerToCurrentScene)->getAllObjectsInScene().size() <= 0) return;

	// Gets the object to follow with the camera. If no object is selected the camera will not move.
	int objectIDToFollow = (*pointerToCurrentScene)->getObjectToFollowID();
	if (objectIDToFollow != -1)
	{
		calculateOffset(*(*pointerToCurrentScene)->getObject(objectIDToFollow), (*pointerToCurrentScene)->getSceneWidth(), (*pointerToCurrentScene)->getSceneHeight());
	}
	else
	{
		videoFacade->setXCameraOffset(0);
		videoFacade->setYCameraOffset(0);
	}

	for (Drawable* obj : (*pointerToCurrentScene)->getAllDrawablesInScene()) {
		if (obj) {
			if((checkInScreen(obj) || checkFixedLayers(obj)) && !obj->getIsRemoved()){
				if (obj->getIsParticle())
				{
					drawParticle((ParticleAdapter*)obj);
				}
				else
				{
					renderCopy(*obj);
				}
			}
		}
	}
}

/// @brief
/// Calls the drawFps method with parameters for all calculated Fps types
void VideoEngine::drawFps() {
	drawFps(FrameData::renderFps, WINDOW_WIDTH, FPS_Y_POSITION_OFFSET, "Fps: ");
}

/// @brief
/// Gathers the given fps data, stores them in structs and passes the data to the videofacade if fps should be drawn
/// @param fps
/// The fps to show on screen
/// @param xPos
/// The X position of where the fps should be drawn
/// @param yPos
/// The Y position of where the fps should be drawn
/// @param prefix
/// The prefix message for the fps
void VideoEngine::drawFps(double fps, int xPos, int yPos, const string& prefix = "fps: ") {
	ostringstream stre;
	stre << prefix << fps;
	string str = stre.str();
	if (shouldDrawFps) {
		ColoredText m(str, Color(NO_RED, NO_BLUE, NO_GREEN), false);
		Position p(xPos, yPos);
		videoFacade->drawMessageAt(m, p, ObjectSize(WINDOW_WIDTH, WINDOW_HEIGHT));
	}
}

/// @brief
/// Toggles fps visibility
bool VideoEngine::toggleFps(Event& fpsEvent) {
	shouldDrawFps = !shouldDrawFps;
	return true;
}

/// @brief Handle the tick update from the thread
bool VideoEngine::receiveTick(Event& tickEvent)
{
	//tickEvent = static_cast<AppTickEvent&>(tickEvent);
	frameData->startTimer();
	clearScreen();
	updateScreen();

	drawFps();
	drawScreen();
	FrameData::renderFps = frameData->calculateAverageFps();

	// do not handle on update events, they are continues
	return false;
}

/// @brief Draws the Particles
/// @param part pointer to the particle
bool VideoEngine::drawParticle(ParticleAdapter* part)
{
	vector<ParticleData> particleData = part->getParticleDataVector();
	for (unsigned int index = 0; index < part->getParticleCount(); index++)
	{
		auto& partData = particleData[index];

		if (partData.size <= 0 || partData.colorA <= 0)
		{
			continue;
		}
		videoFacade->drawParticle(partData, part->GetCurrentSprite().getTextureID());
	}
	// do not handle on update events, they are continues
	return false;
}
