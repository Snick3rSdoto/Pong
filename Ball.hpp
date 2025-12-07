#pragma once
#include <SFML/Graphics.hpp>
#include "Config.hpp"

class Ball {
public:
	Ball(sf::Vector2f startPos);

	void update(sf::Time dt, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) const;

private:
	sf::CircleShape mShape;
	sf::Vector2f	mVelocity;
};
