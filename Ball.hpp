#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Config.hpp"

class Ball {
public:
	Ball(sf::Vector2f startPos, const sf::RenderWindow& window);

	void update(float dt);
	void draw(sf::RenderWindow& window) const;

	const sf::CircleShape getShape() const { return mShape;} 
	sf::FloatRect getBounds() const;

	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f& vel);
	void setPosition(const sf::Vector2f& pos);

private:
	sf::CircleShape mShape;
	sf::Vector2f	mVelocity;
	const sf::RenderWindow* mWindow;
};
