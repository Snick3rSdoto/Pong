#include "Game.hpp"
#include "Config.hpp"
#include "ControlStrategy.hpp"
#include <memory>
#include <SFML/System/Vector2.hpp>

Game::Game()
: mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game")
, mBall(
		sf::Vector2f(
			WINDOW_WIDTH / 2.f - BALL_RADIUS,
			WINDOW_HEIGHT / 2.f - BALL_RADIUS
			), 
		mWindow)
, mPlayerPaddle( // our left paddle
		sf::Vector2f(
			10.f, // move away a bit 
			WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
			),
		mWindow,
		std::make_unique<PlayerControlStrategy>() 
		)
, mOpponentPaddle(  
		sf::Vector2f(
			WINDOW_WIDTH - PADDLE_WIDTH - 10.f, 
			WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
			),
		mWindow,
		std::make_unique<AIControlStrategy>(mBall) // AI follows the ball
		)
{
}

void Game::run() {
	sf::Clock clock{};
    while (mWindow.isOpen()) {
		float dt = clock.restart().asSeconds();

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

void Game::update(float dt) {
	mBall.update(dt);
	mPlayerPaddle.update(dt);
	mOpponentPaddle.update(dt);
}

void Game::render() {
	mWindow.clear(sf::Color::Black);

	mBall.draw(mWindow);
	mPlayerPaddle.draw(mWindow);
	mOpponentPaddle.draw(mWindow);

    mWindow.display();
}
