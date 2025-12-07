#include "Ball.hpp"


Ball::Ball(sf::Vector2f startPos)
	: mShape(BALL_RADIUS)
	, mVelocity(BALL_SPEED, BALL_SPEED)
{
	mShape.setFillColor(sf::Color::White);
	mShape.setPosition(startPos);
}

void Ball::update(sf::Time dt, const sf::RenderWindow& window) {
	float seconds = dt.asSeconds();

	sf::Vector2f pos = mShape.getPosition();
	float diameter = BALL_RADIUS * 2.f;
	sf::Vector2u size = window.getSize();


	//движения
	pos += mVelocity * seconds;


	// отскок по X
    if (pos.x <= 0.f) {
        pos.x = 0.f;
        mVelocity.x *= -1.f;
    } else if (pos.x + diameter >= static_cast<float>(size.x)) {
        pos.x = static_cast<float>(size.x) - diameter;
        mVelocity.x *= -1.f;
    }
	
	// отскок по Y
    if (pos.y <= 0.f) {
        pos.y = 0.f;
        mVelocity.y *= -1.f;
    } else if (pos.y + diameter >= static_cast<float>(size.y)) {
        pos.y = static_cast<float>(size.y) - diameter;
        mVelocity.y *= -1.f;
    }

	mShape.setPosition(pos);

}

void Ball::draw(sf::RenderWindow& window) const {
	window.draw(mShape);
}

