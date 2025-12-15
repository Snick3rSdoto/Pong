#include "Paddle.hpp"
#include "Config.hpp"
#include "ControlStrategy.hpp"
#include "GameObject.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>



Paddle::Paddle(const sf::Vector2f& startPos,
		sf::RenderWindow& window,
		std::unique_ptr<ControlStrategy> controlStrategy,
		float speed)
	: MotionGameObject(window)
	, mShape()
	, mControlStrategy(std::move(controlStrategy))
	, mSpeed(speed)
{
	mShape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
	mShape.setFillColor(sf::Color::White);
	mShape.setPosition(startPos);
}


void Paddle::update(float dt) {

	float paddleCenterY = getCenterY();
	float dir = mControlStrategy->getDirection(paddleCenterY);
	

    sf::Vector2f pos = mShape.getPosition();
	pos.y += dir * mSpeed * dt;


    float windowHeight = static_cast<float>(mWindow.getSize().y);

    if (pos.y < 0.f) {
        pos.y = 0.f;
    } else if (pos.y + PADDLE_HEIGHT > windowHeight) {
        pos.y = windowHeight - PADDLE_HEIGHT;
    }

    mShape.setPosition(pos);

}


float Paddle::getCenterY() const {
    return mShape.getPosition().y + PADDLE_HEIGHT / 2.f;
}

sf::FloatRect Paddle::getBounds() const {
    return mShape.getGlobalBounds();
}

void Paddle::setPosition(const sf::Vector2f& pos) {
    mShape.setPosition(pos);
}

