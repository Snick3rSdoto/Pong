#include "Game.hpp"
#include "Config.hpp"
#include "ControlStrategy.hpp"
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <iostream>

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
	//std::srand(static_cast<unsigned int>(std::time(nullptr)));
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

	handleCollisions();

	std::cout << mPlayerScore << " " << mOpponentScore << "\n";
}

void Game::render() {
	mWindow.clear(sf::Color::Black);

	mBall.draw(mWindow);
	mPlayerPaddle.draw(mWindow);
	mOpponentPaddle.draw(mWindow);

    mWindow.display();
}


void Game::handleCollisions() {
	sf::FloatRect ballBounds     = mBall.getBounds();

	// FIRST we check the goals (touching the left/right wall)
    if (ballBounds.left <= 0.f) {
        ++mOpponentScore;
        resetRound(1); // After goal, the ball will go to the right
        return;
    }
    if (ballBounds.left + ballBounds.width >= static_cast<float>(WINDOW_WIDTH)) {
        ++mPlayerScore;
        resetRound(-1); // to the left
        return;
    }

	sf::Vector2f  ballVelocity   = mBall.getVelocity();

	sf::FloatRect playerBounds   = mPlayerPaddle.getBounds();
	sf::FloatRect opponentBounds = mOpponentPaddle.getBounds();

	// collision with the left paddle (player)
	if (ballBounds.intersects(playerBounds) && ballVelocity.x < 0.f) {
		// pushes out ball right of paddle
		ballBounds.left = playerBounds.left + playerBounds.width;
		mBall.setPosition({ ballBounds.left, ballBounds.top });

		ballVelocity.x = -ballVelocity.x;
		mBall.setVelocity(ballVelocity);
	}

	// updating boundaries after a possible shift
	ballBounds = mBall.getBounds();

	// collision with the right paddle (opponent)
	if (ballBounds.intersects(opponentBounds) && ballVelocity.x > 0.f) {
		// pushes out ball left of paddle
		ballBounds.left = opponentBounds.left - ballBounds.width;
		mBall.setPosition({ ballBounds.left, ballBounds.top });

		ballVelocity.x = -ballVelocity.x;
		mBall.setVelocity(ballVelocity);
	}
}


void Game::resetRound(int direction) {
    sf::Vector2f centerPos(
        WINDOW_WIDTH  / 2.f - BALL_RADIUS,
        WINDOW_HEIGHT / 2.f - BALL_RADIUS
    );
    mBall.reset(centerPos);

	// random Y direction: up or down
    float signY = (std::rand() % 2 == 0 ? 1.f : -1.f);
    sf::Vector2f vel(direction * BALL_SPEED,
                     signY * BALL_SPEED * 0.5f);
    mBall.setVelocity(vel);

    // resetes positions of paddles 
    mPlayerPaddle.setPosition({
        10.f,
        WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
    });
    mOpponentPaddle.setPosition({
        WINDOW_WIDTH - PADDLE_WIDTH - 10.f,
        WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
    });
}

