#include "Game.hpp"
#include <iostream>
#include <ostream>

Game::Game() : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game")
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	initObjects();
}

void Game::initObjects() {

	mBall = std::make_shared<Ball>(
			sf::Vector2f(
				WINDOW_WIDTH  / 2.f - BALL_RADIUS,
				WINDOW_HEIGHT / 2.f - BALL_RADIUS
				),
			mWindow
			);

	mPlayerPaddle = std::make_shared<Paddle>(
			sf::Vector2f(
				10.f, // move away a bit
				WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
				),
			mWindow,
			std::make_unique<PlayerControlStrategy>()
			//PADDLE_SPEED
			);

	mOpponentPaddle = std::make_shared<Paddle>(
			sf::Vector2f(
				WINDOW_WIDTH - PADDLE_WIDTH - 10.f,
				WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
				),
			mWindow,
			std::make_unique<AIControlStrategy>(*mBall), // AI follows the ball
			PADDLE_SPEED * 0.5f //a little slover
			);
	    mFont.loadFromFile("arial.ttf");

    mScoreDisplay = std::make_shared<ScoreDisplay>(
        mWindow,
        mFont,
        mPlayerScore,
        mOpponentScore
    );

    mCenterLine = std::make_shared<CenterLine>(mWindow);

    mObjects.push_back(mCenterLine);
    mObjects.push_back(mScoreDisplay);
    mObjects.push_back(mBall);
    mObjects.push_back(mPlayerPaddle);
    mObjects.push_back(mOpponentPaddle);
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
	for(auto& obj : mObjects) {
		obj->update(dt);
	}

	handleCollisions();

	//std::cout << mPlayerScore << " " << mOpponentScore << "\n";
	
	mScoreText.setString(
			std::to_string(mPlayerScore) + " : " + std::to_string(mOpponentScore)
			);

	//Center the text horizontally, place it on top
	sf::FloatRect bounds = mScoreText.getLocalBounds();
	mScoreText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	mScoreText.setPosition(WINDOW_WIDTH / 2.f, 30.f);
}

void Game::render() {
	mWindow.clear(sf::Color::Black);

	// small centralized line
	sf::RectangleShape centerLine({2.f, static_cast<float>(WINDOW_HEIGHT)});
	centerLine.setFillColor(sf::Color(128, 128, 128));
	centerLine.setPosition(WINDOW_WIDTH / 2.f, 0.f);
	mWindow.draw(centerLine);

	for(auto& obj : mObjects) {
		obj->draw();
	}

	mWindow.draw(mScoreText);

    mWindow.display();
}


void Game::handleCollisions() {
	if(handleGoalCollisions()) { return; }

	handlePaddleCollisions();
}

bool Game::handleGoalCollisions() {
    sf::FloatRect ballBounds = mBall->getBounds();

    if (ballBounds.left <= 0.f) {
        ++mOpponentScore;
        resetRound(1);
        return true;
    }
    if (ballBounds.left + ballBounds.width >= static_cast<float>(WINDOW_WIDTH)) {
        ++mPlayerScore;
        resetRound(-1);
        return true;
    }
    return false;
}

void Game::handlePaddleCollisions() {
    handlePaddleCollision(mPlayerPaddle, true);
    handlePaddleCollision(mOpponentPaddle, false);
}

void Game::handlePaddleCollision(const std::shared_ptr<Paddle>& paddle, bool isLeftPaddle) {
    if (!paddle) { return; }
    sf::FloatRect ballBounds   = mBall->getBounds();
    sf::Vector2f  ballVelocity = mBall->getVelocity();
    sf::FloatRect paddleBounds = paddle->getBounds();

    if (!ballBounds.intersects(paddleBounds)) {
        return;
    } else if (isLeftPaddle && ballVelocity.x >= 0.f) {
        return;
    } else if (!isLeftPaddle && ballVelocity.x <= 0.f) {
        return;
    }

    if (isLeftPaddle) {
        ballBounds.left = paddleBounds.left + paddleBounds.width;
    } else {
        ballBounds.left = paddleBounds.left - ballBounds.width;
    }

    mBall->setPosition({ ballBounds.left, ballBounds.top });

    ballVelocity.x = -ballVelocity.x;
    mBall->setVelocity(ballVelocity);
	std::cout << '\a' << std::flush;
}


void Game::resetRound(int direction) {
    sf::Vector2f centerPos(
        WINDOW_WIDTH  / 2.f - BALL_RADIUS,
        WINDOW_HEIGHT / 2.f - BALL_RADIUS
    );
    mBall->setPosition(centerPos);

	// random Y direction: up or down
    float signY = (std::rand() % 2 == 0 ? 1.f : -1.f);
    sf::Vector2f vel(direction * BALL_SPEED,
                     signY * BALL_SPEED * 0.5f);
    mBall->setVelocity(vel);

    // resetes positions of paddles 
    mPlayerPaddle->setPosition({
        10.f,
        WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
    });
    mOpponentPaddle->setPosition({
        WINDOW_WIDTH - PADDLE_WIDTH - 10.f,
        WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
    });
}

