#include "Engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::init()
{
	window.create(sf::VideoMode(800, 800), "2D Physics Engine", sf::Style::Close | sf::Style::Titlebar);

	// Create objects
	rigid_bodies.push_back(new Circle());
	rigid_bodies[0]->init();
}

void Engine::run()
{
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			}

			//states.back()->handleEvents(e);

		}

		float delta_time = clock.restart().asSeconds();

		update(delta_time);
		render();
	}
}

void Engine::update(float delta_time)
{
	for (int i = 0; i < rigid_bodies.size(); i++)
	{
		rigid_bodies[i]->update(delta_time);
	}
}

void Engine::render()
{
	for (int i = 0; i < rigid_bodies.size(); i++)
	{
		rigid_bodies[i]->render(window);
	}
}