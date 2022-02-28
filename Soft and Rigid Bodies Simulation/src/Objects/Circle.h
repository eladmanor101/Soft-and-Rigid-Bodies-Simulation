#pragma once

#include <SFML/Graphics.hpp>

#include "RigidBody.h"

class Circle : public RigidBody
{
public:
	Circle() = default;
	~Circle() = default;
	
	void init();
	void update(float delta_time);
	void render(sf::RenderWindow& window);

private:
	void handleCollisions(float delta_time);

	sf::Vector2f position;
	sf::Vector2f velocity;
	float mass;

	sf::CircleShape circle_shape;
};