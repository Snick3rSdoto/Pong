#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "GameObject.hpp"
#include "ControlStrategy.hpp"



class Paddle : public GameObject{
public:
	Paddle(sf::Vector2f startPos,
			const sf::RenderWindow& window,
			std::unique_ptr<ControlStrategy> controlStrategy
			);

	void update(float dt) override;
	void draw(sf::RenderWindow& window) override;

	float 		 getCenterY() const;
	sf::FloatRect getBounds() const;

	void setPosition(const sf::Vector2f& pos);

private:
    sf::RectangleShape mShape;
    const sf::RenderWindow* mWindow;
    std::unique_ptr<ControlStrategy> mControlStrategy;

};






