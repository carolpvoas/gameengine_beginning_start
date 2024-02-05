#pragma once

#include "../Beginning/Input.h"

namespace Beginning {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(SDL_Scancode keycode) override;
	};
}