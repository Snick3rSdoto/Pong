#include "Paddle.hpp"
#include "Config.hpp"
#include "ControlStrategy.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>



Paddle::Paddle(sf::Vector2f startPos,
		const sf::RenderWindow& window,
		std::unique_ptr<ControlStrategy> controlStrategy)
	: mShape()
	, mWindow(&window)
	, mControlStrategy(std::move(controlStrategy))
{
	mShape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
	mShape.setFillColor(sf::Color::White);
	mShape.setPosition(startPos);
}


void Paddle::update(float dt) {
	if (!mWindow || !mControlStrategy) return;

	float paddleCenterY = getCenterY();
	// -1, 0, 1 from strategy
	float dir = mControlStrategy->getDirection(dt, paddleCenterY);
	

    sf::Vector2f pos = mShape.getPosition();
	pos.y += dir * PADDLE_SPEED * dt;


	// limit it within the window
    float windowHeight = static_cast<float>(mWindow->getSize().y);

    if (pos.y < 0.f) {
        pos.y = 0.f;
    } else if (pos.y + PADDLE_HEIGHT > windowHeight) {
        pos.y = windowHeight - PADDLE_HEIGHT;
    }

    mShape.setPosition(pos);

}

void Paddle::draw(sf::RenderWindow& window) {
	window.draw(mShape);
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


