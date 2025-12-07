#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "Config.hpp"
#include <SFML/Graphics.hpp>


class Ball {
public:
	Ball(sf::Vector2f startPos);

	void update(sf::Time dt, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) const;

private:
	sf::CircleShape mShape;
	sf::Vector2f	mVelocity;
};

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


class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();

private:
    sf::RenderWindow mWindow;
	Ball			 mBall;
};


Game::Game()
: mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game")
, mBall(sf::Vector2f(
		WINDOW_WIDTH / 2.f - BALL_RADIUS,
		WINDOW_HEIGHT / 2.f - BALL_RADIUS	
		))
{
}

void Game::run() {
	sf::Clock clock{};
    while (mWindow.isOpen()) {
		sf::Time dt = clock.restart();

        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Escape) {
			mWindow.close();
		}
    }
}

void Game::update(sf::Time dt) {
	mBall.update(dt, mWindow);
}

void Game::render() {
	mWindow.clear(sf::Color::Black);

	mBall.draw(mWindow);

    mWindow.display();
}


int main() {
    Game game;
    game.run();
    return 0;
}














