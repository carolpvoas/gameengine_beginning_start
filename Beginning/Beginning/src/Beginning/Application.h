#pragma once


//#include "../Beginning/Events/Event.h"
//#include "Events/ApplicationEvent.h"
#include "../bgpch.h"
#include "../Beginning/Renderer/Renderer.h"
#include "Events/EventHandler.h"

namespace Beginning {

	class Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();

		//	void OnEvent(Event& e);

			static void Close();
		
			
			static Application& Get() { return *s_Instance; }
			
	private:
		bool m_Running = true;

		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<EventHandler> m_EventHandler;

	//	EventHandler* m_EventHandler = new EventHandler();

	private:
		static Application* s_Instance;
	};

	//To be defined in the client
	Application* CreateApplication();

}

