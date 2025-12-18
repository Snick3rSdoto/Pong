#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "Config.hpp"
#include "GameObject.hpp"

class Ball : public GameObject {
public:
    Ball(sf::RenderWindow& window);

    void update(float dt) override;

    void setSize(const sf::Vector2f& size) override;
    sf::Vector2f getCenter() const override;

    sf::FloatRect getBounds() const { return GameObject::getBounds(); }

    void reset(const sf::Vector2f& position);

protected:
    sf::Shape& getShape() override { return mShape; }
    const sf::Shape& getShape() const override { return mShape; }

private:
	sf::CircleShape mShape;
};
