#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

#include "../Math.h"

struct MassPoint
{
	sf::Vector2f position;
	sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f force = sf::Vector2f(0.0f, 0.0f);
	float mass;
	float radius;

	MassPoint(sf::Vector2f position, float mass, float radius)
	{
		this->position = position;
		this->mass = mass;
		this->radius = radius;
	}
};

struct Spring
{
	MassPoint& A;
	MassPoint& B;
	float stiffness;
	float rest_length;
	float damping_factor;

	Spring(MassPoint& A, MassPoint& B, float stiffness, float damping_factor) : A(A), B(B)
	{
		this->stiffness = stiffness;
		this->damping_factor = damping_factor;

		this->rest_length = math::length(B.position - A.position);
	}
};

class SoftBody
{
public:
	SoftBody();
	~SoftBody();

	void init();
	void update(float delta_time);
	void render(sf::RenderWindow& window);

private:
	void handleCollisions(float delta_time);

	std::vector<MassPoint> mass_points;
	std::vector<sf::Vector2f> collision_forces;
	std::vector<Spring> springs;
};