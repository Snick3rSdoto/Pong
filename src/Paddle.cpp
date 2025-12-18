#include "../include/pong/Paddle.hpp"
#include "../include/pong/Config.hpp"
#include "../include/pong/ControlStrategy.hpp"
#include "../include/pong/GameObject.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>



Paddle::Paddle(sf::RenderWindow& window, 
			std::unique_ptr<ControlStrategy> controlStrategy) 
	: GameObject(window)
	, mControlStrategy(std::move(controlStrategy)) {}


void Paddle::update(float dt) {

	if(mControlStrategy) {
		mControlStrategy->updateDirection(*this);
	}

	GameObject::update(dt);

	sf::Vector2f pos  = getPosition();
	sf::Vector2f size = mShape.getSize();
	float windowHeight = static_cast<float>(mWindow.getSize().y);

	if (pos.y < 0.f) {
		pos.y = 0.f;
	} else if (pos.y + size.y > windowHeight) {
		pos.y = windowHeight - size.y;
	}

	setPosition(pos);
}

void Paddle::setSize(const sf::Vector2f& size) {
    mShape.setSize(size);
}

sf::Vector2f Paddle::getCenter() const {
    sf::Vector2f pos  = getPosition();
    sf::Vector2f size = mShape.getSize();

    return { pos.x + size.x / 2.f, pos.y + size.y / 2.f };
}
