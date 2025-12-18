#include "CenterLine.hpp"

CenterLine::CenterLine(sf::RenderWindow& window)
    : GameObject(window)
{
    setSize({2.f, static_cast<float>(WINDOW_HEIGHT)});
    setColor(sf::Color(128, 128, 128));

    setPosition(
        WINDOW_WIDTH / 2.f - 1.f,
        0.f
    );

    setDirection({0.f, 0.f});
    setSpeed(0.f);
}

void CenterLine::update(float /*dt*/) {}

void CenterLine::setSize(const sf::Vector2f& size) {
    mShape.setSize(size);
}

sf::Vector2f CenterLine::getCenter() const {
    sf::Vector2f pos  = getPosition();
    sf::Vector2f size = mShape.getSize();

    return { pos.x + size.x / 2.f, pos.y + size.y / 2.f };
}

