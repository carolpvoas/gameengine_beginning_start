#include "../bgpch.h"

#include "WindowsInput.h"

//#include "../Beginning/Application.h"
#include "SDL.h"

namespace Beginning {

    Input* Input::s_Instance = new WindowsInput();
   
	bool WindowsInput::IsKeyPressedImpl(SDL_Scancode keycode)
	{
        const Uint8* state = SDL_GetKeyboardState(NULL);
        return state[keycode] == 1;
        
       // return m_keycode == SDL_PRESSED;
      //  return true;
	}
}