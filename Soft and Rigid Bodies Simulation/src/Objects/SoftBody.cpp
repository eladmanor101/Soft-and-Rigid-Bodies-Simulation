#include "SoftBody.h"

SoftBody::SoftBody()
{

}

SoftBody::~SoftBody()
{

}

void SoftBody::init()
{
	mass_points.push_back(MassPoint(sf::Vector2f(100.0f, 100.0f), 10.0f, 10.0f));
	mass_points.push_back(MassPoint(sf::Vector2f(200.0f, 100.0f), 10.0f, 10.0f));
	mass_points.push_back(MassPoint(sf::Vector2f(100.0f, 200.0f), 10.0f, 10.0f));
	mass_points.push_back(MassPoint(sf::Vector2f(200.0f, 200.0f), 10.0f, 10.0f));

	for (int i = 0; i < mass_points.size(); i++)
	{
		collision_forces.push_back(sf::Vector2f(0.0f, 0.0f));
	}

	springs.push_back(Spring(mass_points[0], mass_points[1], 3.0f, 50.0f));
	springs.push_back(Spring(mass_points[0], mass_points[2], 3.0f, 50.0f));
	springs.push_back(Spring(mass_points[0], mass_points[3], 3.0f, 50.0f));
	springs.push_back(Spring(mass_points[1], mass_points[2], 3.0f, 50.0f));
	springs.push_back(Spring(mass_points[1], mass_points[3], 3.0f, 50.0f));
	springs.push_back(Spring(mass_points[2], mass_points[3], 3.0f, 50.0f));
}

void SoftBody::update(float delta_time)
{
	for (int i = 0; i < mass_points.size(); i++)
	{
		MassPoint& point = mass_points[i];

		point.force = sf::Vector2f(0.0f, 0.0f);
		point.force += sf::Vector2f(0.0f, 9.81f * point.mass);
		point.force += collision_forces[i] * point.mass;
	}

	for (Spring& spring : springs)
	{
		sf::Vector2f position_diff = spring.B.position - spring.A.position;
		float distance = math::length(position_diff);
		position_diff = math::normalize(position_diff);
		sf::Vector2f velocity_diff = spring.B.velocity - spring.A.velocity;

		float force = spring.stiffness * (distance - spring.rest_length) + math::dot(position_diff, velocity_diff) * spring.damping_factor;
	
		spring.A.force += position_diff * force;
		spring.B.force -= position_diff * force;
	}

	for (MassPoint& point : mass_points)
	{
		point.velocity += point.force * 1.0f / point.mass * delta_time;
		point.position += point.velocity * delta_time;
	}

	handleCollisions(delta_time);
}

void SoftBody::render(sf::RenderWindow& window)
{
	for (Spring& spring : springs)
	{
		sf::Vertex line[2];
		line[0].position = spring.A.position;
		line[0].color = sf::Color::White;
		line[1].position = spring.B.position;
		line[1].color = sf::Color::White;

		window.draw(line, 2, sf::Lines);
	}

	for (MassPoint& point : mass_points)
	{
		sf::CircleShape red_circle(point.radius);
		red_circle.setOrigin(red_circle.getRadius(), red_circle.getRadius());
		red_circle.setFillColor(sf::Color::Red);
		red_circle.setPosition(point.position);
		window.draw(red_circle);
	}
}

void SoftBody::handleCollisions(float delta_time)
{
	for (int i = 0; i < mass_points.size(); i++)
	{

		MassPoint& point = mass_points[i];

		if (point.position.y + point.radius > 800.0f)
		{
			sf::Vector2f relative_velocity = point.velocity;
			sf::Vector2f normal = sf::Vector2f(0.0f, -1.0f);
			float velocity_along_normal = math::dot(relative_velocity, normal);

			if (velocity_along_normal > 0)
				continue;

			float e = 0.5f;

			float j = -(1 + e) * velocity_along_normal;
			j /= 1 / point.mass;

			// Apply impulse
			sf::Vector2f impulse = j * normal;
			point.velocity -= 1.0f / point.mass * impulse;
		}

		/*
		if (point.position.y + point.radius > 800.0f)
		{
			float d = point.position.y + point.radius - 800.0f;
			float angle = atanf(fabsf(point.velocity.y) / fabsf(point.velocity.x));
			float length = d / sinf(angle);

			point.position -= math::normalize(point.velocity) * length;
			collision_forces[i] = sf::Vector2f(0.0f, -point.force.y);
		}
		else
		{
			collision_forces[i] = sf::Vector2f(0.0f, 0.0f);
		}*/
	}
}