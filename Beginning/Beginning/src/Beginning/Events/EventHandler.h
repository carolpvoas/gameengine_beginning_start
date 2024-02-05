#pragma once
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "../../bgpch.h"
#include "../Application.h"
#include <SDL.h>

namespace Beginning
{
    class EventHandler
    {
    public:
        EventHandler();
        ~EventHandler();

        //void Update(SDL_Event event);

        //bool OnClose();

        //bool closed;

    private:
        // Add any private members here
    };
}

#endif // EVENTHANDLER_H