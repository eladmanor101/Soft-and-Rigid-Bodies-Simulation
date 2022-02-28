#include "Math.h"

float math::dot(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f math::normalize(sf::Vector2f v)
{
	return 1.0f / sqrtf(v.x * v.x + v.y * v.y) * v;
}


float math::length(sf::Vector2f v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}