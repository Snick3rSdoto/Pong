#include "Ball.hpp"
#include "GameObject.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


Ball::Ball(sf::RenderWindow& window)
	: GameObject(window)
	, mShape(BALL_RADIUS)
{
	mShape.setFillColor(sf::Color::White);

	setSpeed(BALL_SPEED);
	setDirection({1.f, 0.5});
}


void Ball::update(float dt) {

	GameObject::update(dt);

	sf::Vector2f pos = getPosition();
	float diameter = BALL_RADIUS * 2.f;
	sf::Vector2u size = mWindow.getSize();

	if (pos.y <= 0.f) {
		pos.y = 0.f;
		auto dir = getDirection();
		dir.y = -dir.y;
		setDirection(dir);
	} else if (pos.y + diameter >= static_cast<float>(size.y)) {
		pos.y = static_cast<float>(size.y) - diameter;
		auto dir = getDirection();
		dir.y = -dir.y;
		setDirection(dir);
	}
	setPosition(pos);
}


void Ball::setSize(const sf::Vector2f& size) {
    float radius = std::min(size.x, size.y) * 0.5f;
    mShape.setRadius(radius);
}

sf::Vector2f Ball::getCenter() const {
    sf::Vector2f pos = getPosition();
    float r = mShape.getRadius();
    return { pos.x + r, pos.y + r };
}

void Ball::reset(const sf::Vector2f& position) {
    setPosition(position);
}
