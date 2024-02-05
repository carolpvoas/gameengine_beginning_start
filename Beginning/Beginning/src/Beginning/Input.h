#pragma once


#include "KeyCodes.h"

#include "SDL.h"

namespace Beginning {

	class Input
	{
	public:
		static bool IsKeyPressed(SDL_Scancode keycode) { return s_Instance->IsKeyPressedImpl(keycode); };

	protected:
		virtual bool IsKeyPressedImpl(SDL_Scancode keycode) = 0;

	private:
		static Input* s_Instance;
	};
}