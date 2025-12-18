#include "ControlStrategy.hpp"
#include "Ball.hpp"
#include <SFML/Window/Keyboard.hpp>

float PlayerControlStrategy::getDirection(float /*paddleCenterY*/) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		return -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		return 1.f;
    return 0.f;
}

AIControlStrategy::AIControlStrategy(const Ball& ball)
    : m_ball(ball)
{}

float AIControlStrategy::getDirection(float paddleCenterY) {
	sf::Vector2f ballCenter = m_ball.getCenter();
	float ballCenterY = ballCenter.y;

    constexpr const float deadZone = 10.f;
    if (ballCenterY < paddleCenterY - deadZone)
        return -1.f;
    if (ballCenterY > paddleCenterY + deadZone)
        return 1.f;
    return 0.f;
}

