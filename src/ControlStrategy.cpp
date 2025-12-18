#include "ControlStrategy.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include <SFML/Window/Keyboard.hpp>


void PlayerControlStrategy::updateDirection(Paddle& paddle) {
	float dirY = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		dirY -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		dirY += 1.f;

	paddle.setDirection({0.f, dirY});
}

AIControlStrategy::AIControlStrategy(std::shared_ptr<Ball> ball)
	: mBall(std::move(ball))
{}

void AIControlStrategy::updateDirection(Paddle& paddle) {
	if (!mBall) {
		paddle.setDirection({0.f, 0.f});
		return;
    }
	sf::Vector2f paddleCenter = paddle.getCenter();
    float paddleCenterY = paddleCenter.y;

    sf::Vector2f ballCenter   = mBall->getCenter();
    float ballCenterY = ballCenter.y;

    constexpr float deadZone = 10.f;
    float dirY = 0.f;

    if (ballCenterY < paddleCenterY - deadZone)
        dirY = -1.f;
    else if (ballCenterY > paddleCenterY + deadZone)
        dirY = 1.f;
    else
        dirY = 0.f;

    paddle.setDirection({0.f, dirY});
}

