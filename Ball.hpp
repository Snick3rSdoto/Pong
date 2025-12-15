#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "Config.hpp"
#include "GameObject.hpp"

class Ball : public MotionGameObject {
public:
	Ball(const sf::Vector2f& startPos, sf::RenderWindow& window);

	void update(float dt) override;

	const sf::CircleShape& getCircleShape() const { return mShape;} 
	sf::FloatRect getBounds() const;

	const sf::Vector2f& getVelocity() const { return mVelocity; }
	void setVelocity(const sf::Vector2f& vel);
	void setPosition(const sf::Vector2f& pos);

protected:
	sf::Drawable& getDrawable() override { return mShape; }

private:
	sf::CircleShape mShape;
	sf::Vector2f	mVelocity;
};
