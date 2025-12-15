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
	Paddle(const sf::Vector2f& startPos,
			sf::RenderWindow& window,
			std::unique_ptr<ControlStrategy> controlStrategy,
			float speed = PADDLE_SPEED
			);

	void update(float dt) override;

	float getCenterY() const;
	void  setSpeed(float speed) { mSpeed = speed; }
	float getSpeed() const 		{ return mSpeed; }

protected:
    sf::Shape& getShape() override;
    const sf::Shape& getShape() const override;

private:
    sf::RectangleShape              mShape;
    std::unique_ptr<ControlStrategy> mControlStrategy;
    float                            mSpeed;
};
