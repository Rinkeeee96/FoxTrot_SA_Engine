#include "glpch.h"
#include "Renderer2d.h"

namespace Glitch {

	/// @brief 
	/// Inits SDL2 renderer on window
	void Renderer2d::Init(vector<Object*>* objectpointer)
	{
		this->pointerToObjectVector = objectpointer;
		facadeTest->createRenderer();
	}

	void Renderer2d::OnUpdate()
	{
		clearScreen();
		renderSprites();
		drawScreen();
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
	/// Load a animated sprite (PNG) into the AnimatedTexture map
	/// @param spriteID 
	/// @param filename
	/// @param height of 1 single animation sprite
	/// @param widht of 1 single animation sprite
	/// @param amount of animations of 1 sprite
	void Renderer2d::loadSprite(int spriteID, const char* filename, int singleSpriteHeight, int singleSpriteWidth, int size) {
		bool exists = std::filesystem::exists(filename);
		if (!exists)
			throw ERROR_CODE_IMAGE_FILE_NOT_FOUND;
		facadeTest->loadSprite(spriteID, filename, singleSpriteHeight, singleSpriteWidth, size);
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