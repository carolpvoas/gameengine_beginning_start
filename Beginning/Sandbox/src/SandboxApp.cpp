#include <Beginning.h>

/*
class ExampleLayer
{
public:

	
	void OnUpdate() override
	{
		//BG_INFO("ExampleLayer::Update");

		if (Beginning::Input::IsKeyPressed(BG_KEY_B))
		{
			BG_INFO("The B key is pressed!");
		}
		else
		{
		//	std::cout << Beginning::Key::A << std::endl;
			//std::cout << "meh" << std::endl;
		}
	}

	void OnEvent(Beginning::Event& event) override
	{
		//BG_TRACE("{0}", event);
		if (event.GetEventType() == Beginning::EventType::KeyPressed)
		{
			Beginning::KeyPressedEvent& e = (Beginning::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BG_KEY_A)
			{
				std::cout << "PRESSED A" << std::endl;
			}
			
			BG_TRACE("{0}", e.GetKeyCode());
		}
		
	}

	
};*/

class Sandbox : public Beginning::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Beginning::Application* Beginning::CreateApplication()
{
	return new Sandbox();
}
