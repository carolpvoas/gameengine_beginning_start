#include "EventHandler.h"

namespace Beginning {

	EventHandler::EventHandler()
	{
	}

	EventHandler::~EventHandler()
	{
	}
	/*
	void EventHandler::Update(SDL_Event event)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				EventHandler::OnClose();
				break;
			}
		}
	}

	bool EventHandler::OnClose()
	{
		EventHandler::closed = true;
		return closed;
	}*/

}

