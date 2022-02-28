#pragma once

#include "SFML/Graphics.hpp"

namespace math
{
	float dot(sf::Vector2f v1, sf::Vector2f v2);

	sf::Vector2f normalize(sf::Vector2f v);

	float length(sf::Vector2f v);
}