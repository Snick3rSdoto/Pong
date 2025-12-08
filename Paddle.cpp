#include "Paddle.hpp"
#include "Config.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>



Paddle::Paddle(sf::Vector2f startPos) {
	mShape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
	mShape.setFillColor(sf::Color::White);
	mShape.setPosition(startPos);
}


void Paddle::update(sf::Time dt, const sf::RenderWindow& window) {
	float seconds = dt.asSeconds();

    float velocityY = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocityY -= PADDLE_SPEED; // up 
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocityY += PADDLE_SPEED; // down
    }

    sf::Vector2f pos = mShape.getPosition();

    // moves paddle
    pos.y += velocityY * seconds;

	// limit it within the window
    float windowHeight = static_cast<float>(window.getSize().y);

    if (pos.y < 0.f) {
        pos.y = 0.f;
    } else if (pos.y + PADDLE_HEIGHT > windowHeight) {
        pos.y = windowHeight - PADDLE_HEIGHT;
    }

    mShape.setPosition(pos);

}

void Paddle::draw(sf::RenderWindow& window) const {
	window.draw(mShape);
}










