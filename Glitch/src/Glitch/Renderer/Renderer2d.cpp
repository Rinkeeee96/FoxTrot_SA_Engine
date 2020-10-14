#include "glpch.h"
#include "Renderer2d.h"

namespace Glitch {

	/// @brief 
	/// Inits SDL2 renderer on window
	void Renderer2d::Init(vector<Object*>* objectpointer)
	{
		this->pointerToObjectVector = objectpointer;
		frameData = new FrameData;
		facadeTest->createRenderer();
	}

	void Renderer2d::OnUpdate()
	{
		frameData->startTimer();
		clearScreen();
		renderSprites();
		if (shouldDrawFps) {
			drawFps();
		}
		drawScreen();
		FrameData::renderFps = frameData->calculateAverageFps();
	}

	void Renderer2d::Shutdown()
	{
		facadeTest->deallocateSurface();
	}

	void Renderer2d::renderSprites()
	{
		if (pointerToObjectVector == nullptr) return;
		//if (pointerToObjectVector->capacity() <= 0) return;
		for (Object* obj : *pointerToObjectVector) {
			if (obj != nullptr) {
				facadeTest->renderCopy(*obj);
			}
		}
	}

	/// @brief
	/// Toggles the fps counter
	void Renderer2d::toggleFps() {
		shouldDrawFps = !shouldDrawFps;
	}

	/// @brief 
	/// Clears SDL screen
	void Renderer2d::clearScreen()
	{
		facadeTest->clearScreen();
	}

	/// @brief 
	/// Draws SDL screen
	void Renderer2d::drawScreen()
	{
		facadeTest->drawScreen();
	}

	/// @brief
	/// Calls the drawFps function for all fps counters
	void Renderer2d::drawFps() {
		drawFps(FrameData::loopFps, X_ZERO, Y_ZERO, "Game Fps: ");
		drawFps(FrameData::loopFps, X_ZERO, SDL_FPS_Y, "SDL Fps: ");
	}

	/// @brief
	/// Draws the fps if toggled on
	void Renderer2d::drawFps(double fps, int x, int y, const string& prefix = "fps: ")
	{
		ostringstream stre;
		stre << prefix << fps;
		string str = stre.str();
		if (shouldDrawFps) {
			Message m(str, NO_RED, NO_BLUE, NO_GREEN);
			Position p(x, y);
			facadeTest->drawMessageAt(m, p);
		}
	}

	/// @brief 
	/// Loads PNG files and makes them textures to be added to the unordered map
	/// @param spriteID 
	/// @param filename 
	void Renderer2d::loadImage(int spriteID, const char* filename)
	{
		// TODO error if file cannot be found
		bool exists = std::filesystem::exists(filename);
		facadeTest->loadImage(spriteID, filename);
	}

	/// @brief 
	/// Takes the sprites from the Textuture map and copys them to the screen
	/// @param spriteID 
	/// @param xPos 
	/// @param yPos 
	/// @param width 
	/// @param height 
	/// @param rotation 
	void Renderer2d::renderCopy(Object& object)
	{
		facadeTest->renderCopy(object);
	}
}