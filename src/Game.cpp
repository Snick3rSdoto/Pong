#include "Game.hpp"
#include <iostream>
#include <ostream>

Game::Game() : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game")
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	initObjects();
}

void Game::initObjects() {
	if (!mFont.loadFromFile("arial.ttf")) {
    	std::cerr << "Failed to load font\n";
	}

	mCenterLine = std::make_shared<CenterLine>(mWindow);
	

	mScoreDisplay = std::make_shared<ScoreDisplay>(mWindow, mFont);
	mScoreDisplay->setSize({220.f, 60.f});
	mScoreDisplay->setPosition(
			WINDOW_WIDTH / 2.f - 110.f,
			10.f
			);


	mBall = std::make_shared<Ball>(mWindow);
    mBall->setColor(sf::Color::White);
    mBall->setPosition(
        WINDOW_WIDTH  / 2.f - BALL_RADIUS,
        WINDOW_HEIGHT / 2.f - BALL_RADIUS
    );
    mBall->setSpeed(BALL_SPEED);
    mBall->setDirection({1.f, 0.5f});


    mPlayerPaddle = std::make_shared<Paddle>(
        mWindow,
        std::make_unique<PlayerControlStrategy>()
    );
    mPlayerPaddle->setColor(sf::Color::White);
    mPlayerPaddle->setSize({PADDLE_WIDTH, PADDLE_HEIGHT});
    mPlayerPaddle->setPosition(
        10.f,
        WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
    );
    mPlayerPaddle->setSpeed(PADDLE_SPEED);


    mOpponentPaddle = std::make_shared<Paddle>(
        mWindow,
        std::make_unique<AIControlStrategy>(mBall)
    );
    mOpponentPaddle->setColor(sf::Color::White);
    mOpponentPaddle->setSize({PADDLE_WIDTH, PADDLE_HEIGHT});
    mOpponentPaddle->setPosition(
        WINDOW_WIDTH - PADDLE_WIDTH - 10.f,
        WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
    );
    mOpponentPaddle->setSpeed(PADDLE_SPEED * 0.5f);


    mObjects.push_back(mBall);
    mObjects.push_back(mPlayerPaddle);
    mObjects.push_back(mOpponentPaddle);
	mObjects.push_back(mCenterLine);
	mObjects.push_back(mScoreDisplay);
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
}

void Game::render() {
	mWindow.clear(sf::Color::Black);

	for(auto& obj : mObjects) {
		obj->draw();
	}
    mWindow.display();
}


void Game::handleCollisions() {
	if(handleGoalCollisions()) { return; }

	handlePaddleCollisions();
}

bool Game::handleGoalCollisions() {
    sf::FloatRect ballBounds = mBall->getBounds();

    if (ballBounds.left <= 0.f) {
		mScoreDisplay->increment(ScoreOwner::Ai);
        resetRound(1);
        return true;
    }
    if (ballBounds.left + ballBounds.width >= static_cast<float>(WINDOW_WIDTH)) {
        mScoreDisplay->increment(ScoreOwner::Player);
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
    sf::Vector2f  ballDir = mBall->getDirection();
    sf::FloatRect paddleBounds = paddle->getBounds();

    if (!ballBounds.intersects(paddleBounds)) {
        return;
    } else if (isLeftPaddle && ballDir.x >= 0.f) {
        return;
    } else if (!isLeftPaddle && ballDir.x <= 0.f) {
        return;
    }

    if (isLeftPaddle) {
        ballBounds.left = paddleBounds.left + paddleBounds.width;
    } else {
        ballBounds.left = paddleBounds.left - ballBounds.width;
    }

    mBall->setPosition({ ballBounds.left, ballBounds.top });

    ballDir.x = -ballDir.x;
    mBall->setDirection(ballDir);
	std::cout << '\a' << std::flush;
}


void Game::resetRound(int direction) {
    sf::Vector2f centerPos(
        WINDOW_WIDTH  / 2.f - BALL_RADIUS,
        WINDOW_HEIGHT / 2.f - BALL_RADIUS
    );
    mBall->setPosition(centerPos);

    float signY = (std::rand() % 2 == 0 ? 1.f : -1.f);
	sf::Vector2f dirVec(direction * 1.f, signY * 0.5f);
	mBall->setDirection(dirVec);
	mBall->setSpeed(BALL_SPEED);

    mPlayerPaddle->setPosition({
        10.f,
        WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
    });
    mOpponentPaddle->setPosition({
        WINDOW_WIDTH - PADDLE_WIDTH - 10.f,
        WINDOW_HEIGHT / 2.f - PADDLE_HEIGHT / 2.f
    });
}

