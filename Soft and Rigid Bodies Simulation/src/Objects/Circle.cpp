#include "Circle.h"

void Circle::init()
{
	circle_shape.setRadius(20.0f);
	circle_shape.setFillColor(sf::Color::Red);
	circle_shape.setOrigin(circle_shape.getRadius() / 2, circle_shape.getRadius() / 2);

	mass = 1.0f;
}

void Circle::update(float delta_time)
{
	velocity.y += 9.8f;
	position += velocity * delta_time;
}

void Circle::render(sf::RenderWindow& window)
{
	circle_shape.setPosition(position);
	window.draw(circle_shape);
}

void Circle::handleCollisions(float delta_time)
{
	
}