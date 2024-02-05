#include "Application.h"

//#include "Events/ApplicationEvent.h"
#include "Log.h"
#include <SDL.h>
#include "glad/glad.h"
#include "Renderer/Renderer.h"
#include "Events/EventHandler.h"

#include "Input.h"

namespace Beginning {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
	//	m_Window = std::unique_ptr<Window>(Window::Create());
	//	m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

	//	m_Object.reset(new Object());
	//	m_Object->CreateObject();
	//	m_Renderer;
	//	Renderer myRenderer(Renderer::RendererType::Sprite); 

		//m_Renderer->InitRenderer(800, 700);
		m_Renderer.reset(new Renderer(Renderer::RendererType::Sprite));
		//m_EventHandler.reset(new Events());

	}
		

	Application::~Application()
	{
	}


	void Application::Close()
	{
	//	m_Running = false;
	}



	void Application::Run()
	{
			while (m_Running)
			{
				m_Renderer->Update();
				//m_Running = m_EventHandler->OnClose();

			}
			m_Renderer->~Renderer();

	}

}
