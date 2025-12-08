#include "ControlStrategy.hpp"
#include "Ball.hpp"
#include <SFML/Window/Keyboard.hpp>

float PlayerControlStrategy::getDirection(float /*dt*/, float /*paddleCenterY*/) {
    float dir = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        dir -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        dir += 1.f;

    return dir;
}

AIControlStrategy::AIControlStrategy(const Ball& ball)
    : m_ball(ball)
{}

// Very simple AI: the racket tries to keep the center level with the center of the ball
float AIControlStrategy::getDirection(float /*dt*/, float paddleCenterY) {
    const auto& shape = m_ball.getShape();
    float ballCenterY = shape.getPosition().y + shape.getRadius();

    const float deadZone = 10.f; // to keep it from twitching
    if (ballCenterY < paddleCenterY - deadZone)
        return -1.f;
    if (ballCenterY > paddleCenterY + deadZone)
        return 1.f;
    return 0.f;
}

