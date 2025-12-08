#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class Paddle {
public:
	Paddle(sf::Vector2f startPos);

	void update(sf::Time dt, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) const;

private:
	sf::RectangleShape mShape;
};






