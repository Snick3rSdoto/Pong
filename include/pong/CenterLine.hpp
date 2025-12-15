#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Config.hpp"

class CenterLine : public StaticGameObject {
public:
    explicit CenterLine(sf::RenderWindow& window);

protected:
    sf::Drawable& getDrawable() override { return mShape; }

private:
    sf::RectangleShape mShape;
};

