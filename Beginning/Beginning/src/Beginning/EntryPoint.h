#pragma once

#include "../Beginning/Application.h"

#undef main

extern Beginning::Application* Beginning::CreateApplication();

int main(int argc, char** argv)
{
	Beginning::Log::Init();
	//Beginning::Render::Init_SDL();

	BG_CORE_WARN("Initialized Log!");
	BG_INFO("Hello");

	//Beginning::Renderer::;


	auto app = Beginning::CreateApplication();
	app->Run();
	delete app; //TO-DO: RESOLVE EXCEPTION BY COMMETING THE CODE UNTIL YOU FIND SOMETHING (APPLICATION.CPP)
	return 0;
}

