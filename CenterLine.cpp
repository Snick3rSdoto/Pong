#include "CenterLine.hpp"

CenterLine::CenterLine(sf::RenderWindow& window)
    : StaticGameObject(window)
    , mShape()
{
    mShape.setSize({2.f, static_cast<float>(WINDOW_HEIGHT)});
    mShape.setFillColor(sf::Color(128, 128, 128));
    mShape.setPosition(WINDOW_WIDTH / 2.f, 0.f);
}

