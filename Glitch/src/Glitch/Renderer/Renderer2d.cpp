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

	/// @brief 
	/// Updates screen, draw and renders the sprites
	void Renderer2d::OnUpdate()
	{
		clearScreen();
		renderSprites();
		drawScreen();
	}

	/// @brief 
	/// Calls deallocateSurface in the facade, clean up to prevent memory leaks
	void Renderer2d::Shutdown()
	{
		facadeTest->deallocateSurface();
	}

	/// @brief 
	/// Inits SDL2 renderer on window
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