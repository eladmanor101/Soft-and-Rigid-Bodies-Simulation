#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Objects/RigidBody.h"
#include "Objects/Circle.h"

class Engine
{
public:
	Engine();
	~Engine();

	void init();
	void run();

private:
	void update(float delta_time);
	void render();

	sf::RenderWindow window;
	sf::Clock clock;

	std::vector<RigidBody*> rigid_bodies;
};