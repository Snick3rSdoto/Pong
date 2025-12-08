#include "Game.hpp"
#include "Config.hpp"
#include <SFML/System/Vector2.hpp>

Game::Game()
: mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game")
, mBall(sf::Vector2f(
		WINDOW_WIDTH / 2.f - BALL_RADIUS,
		WINDOW_HEIGHT / 2.f - BALL_RADIUS	
		))
, mPaddle(sf::Vector2f (
		10.f,	//move away a bit
		WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
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
	mPaddle.update(dt, mWindow);
}

void Game::render() {
	mWindow.clear(sf::Color::Black);

	mBall.draw(mWindow);
	mPaddle.draw(mWindow);

    mWindow.display();
}
