#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include "Config.hpp"
#include "GameObject.hpp"
#include "ControlStrategy.hpp"



class Paddle : public GameObject{
public:
	Paddle(sf::RenderWindow& window,
			std::unique_ptr<ControlStrategy> controlStrategy);
	void update(float dt) override;

	void setSize(const sf::Vector2f& size) override;
	sf::Vector2f getCenter() const override;

protected:
    sf::Shape& getShape() override { return mShape; }
    const sf::Shape& getShape() const override { return mShape; }

private:
    sf::RectangleShape               mShape;
    std::unique_ptr<ControlStrategy> mControlStrategy;
};
