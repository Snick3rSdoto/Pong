#include "Ball.hpp"
#include <SFML/Graphics/RenderWindow.hpp>


Ball::Ball(sf::Vector2f startPos, const sf::RenderWindow& window)
	: mShape(BALL_RADIUS)
	, mVelocity(BALL_SPEED, BALL_SPEED)
	, mWindow(&window)
{
	mShape.setFillColor(sf::Color::White);
	mShape.setPosition(startPos);
}

void Ball::update(float dt) {
	if(!mWindow) { return; }


	sf::Vector2f pos = mShape.getPosition();
	float diameter = BALL_RADIUS * 2.f;
	sf::Vector2u size = mWindow->getSize();


	//movement
	pos += mVelocity * dt;


	// rebound by X
    if (pos.x <= 0.f) {
        pos.x = 0.f;
        mVelocity.x *= -1.f;
    } else if (pos.x + diameter >= static_cast<float>(size.x)) {
        pos.x = static_cast<float>(size.x) - diameter;
        mVelocity.x *= -1.f;
    }
	
	// rebound by Y
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


sf::FloatRect Ball::getBounds() const {
    return mShape.getGlobalBounds();
}

sf::Vector2f Ball::getVelocity() const {
    return mVelocity;
}

void Ball::setVelocity(const sf::Vector2f& vel) {
    mVelocity = vel;
}

void Ball::setPosition(const sf::Vector2f& pos) {
    mShape.setPosition(pos);
}


