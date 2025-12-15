#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class GameObject {
public:
    explicit GameObject(sf::RenderWindow& window)
        : mWindow(window) {}

    virtual ~GameObject() = default;

    virtual void update(float dt) = 0;

    void draw() {
        mWindow.draw(getShape());
    }

    sf::Vector2f getPosition() const {
        return getShape().getPosition();
    }

    void setPosition(const sf::Vector2f& pos) {
        getShape().setPosition(pos);
    }

    sf::FloatRect getBounds() const {
        return getShape().getGlobalBounds();
    }

protected:
    virtual sf::Shape& getShape() = 0;
    virtual const sf::Shape& getShape() const = 0;

    sf::RenderWindow& mWindow;
};
