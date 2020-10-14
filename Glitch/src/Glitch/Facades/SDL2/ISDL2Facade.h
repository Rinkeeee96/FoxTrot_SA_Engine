#pragma once
#include "Glitch/Core/Object.h"

namespace Glitch {

	struct Message {
		Message::Message(const string& _text, int _r, int _g, int _b)
			: text{ _text }, r{ _r }, g{ _g }, b{ _b }{}
		const string& text;
		int r, g, b;
	};

	struct Position {
		Position::Position(int _x, int _y) : x{ _x }, y{ _y } {}
		int x, y;
	};

	struct Size {
		int w, h;
	};

	class ISDL2Facade
	{
	public:
		ISDL2Facade() {};
		~ISDL2Facade() {};

		// window facade
		// renderer facade
		// facade abstraheren naar generieke functionaliteit

		virtual void createWindow(WindowProps* props) = 0;
		virtual void destroyScreen() = 0;
		virtual SDL_Window* getWindow() = 0;

		virtual void createRenderer() = 0;
		virtual void clearScreen() = 0;
		virtual void drawScreen() = 0;
		virtual void loadImage(int spriteID, const char* filename) = 0;
		virtual void renderCopy(Object& object) = 0;
		//virtual void renderCopy(Glitch::Object* o) = 0;
		virtual void drawMessageAt(const Message& message, const Position& pos) = 0;

		virtual void deallocateSurface() = 0;

		virtual void Init() = 0;


	private:

	};

}