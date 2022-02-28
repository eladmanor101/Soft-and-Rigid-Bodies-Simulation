#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

class RigidBody
{
public:
	RigidBody() = default;
	virtual ~RigidBody() = default;

	virtual void init() = 0;
	virtual void update(float delta_time) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

private:
	virtual void handleCollisions(float delta_time) = 0;
};