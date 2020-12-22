#include "stdafx.h"

#include "InputFacade.h"
#include "Commands/KeypressInvoker.h"

#include <SDL.h>

#undef main

/// @brief
/// Poll the input events and dispatch a KeyPressedEvent
void InputFacade::pollEvents() {
	SDL_Event sdl_event;
	if (&sdl_event)
	{
		while (SDL_PollEvent(&sdl_event))
		{
			switch (sdl_event.type)
			{
			case SDL_MOUSEMOTION: {
				int x, y;
				SDL_GetMouseState(&x, &y);

				MouseMovedEvent event((float)x, (float)y);
				dispatcher.dispatchEvent<MouseMovedEvent>(event);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				int keycode = sdl_event.button.button; 
				MouseButtonPressed event((MouseCode)keycode);
				dispatcher.dispatchEvent<MouseButtonPressed>(event);
				return;
			}
			case SDL_KEYDOWN: 
			{
				// Command queue with events to fire
				KeyPressedEvent event((KeyCode)sdl_event.key.keysym.scancode, 1);
				dispatcher.dispatchEvent<KeyPressedEvent>(event);
				break;
			}
			case SDL_KEYUP: {
				KeyReleasedEvent event((KeyCode)sdl_event.key.keysym.scancode);
				dispatcher.dispatchEvent<KeyReleasedEvent>(event);
				break;
			}
			case SDL_QUIT: {
				break;
			}
			default:
				break;
			}
		}
	}
}

KeyCode InputFacade::getSingleKeyStroke()
{
	SDL_Event sdl_event;
	if (&sdl_event)
	{
		while (true) {
			while (SDL_PollEvent(&sdl_event))
			{
				switch (sdl_event.type) {
					case SDL_KEYDOWN:
					{
						return KeyCode(sdl_event.key.keysym.scancode);
					}
				}
			}
		}
	}
}
