#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};

class DrawableGameObject : public GameObject {
public:
    explicit DrawableGameObject(sf::RenderWindow& window)
        : mWindow(window) {}

protected:
    sf::RenderWindow& mWindow;

    virtual sf::Drawable& getDrawable() = 0;

public:
    void draw() override {
        mWindow.draw(getDrawable());
    }
};

class StaticGameObject : public DrawableGameObject {
public:
    using DrawableGameObject::DrawableGameObject;

    void update(float) override {}
};

class MotionGameObject : public DrawableGameObject {
public:
    using DrawableGameObject::DrawableGameObject;
};
