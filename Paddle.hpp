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



class Paddle : public MotionGameObject{
public:
	Paddle(const sf::Vector2f& startPos,
			sf::RenderWindow& window,
			std::unique_ptr<ControlStrategy> controlStrategy,
			float speed = PADDLE_SPEED
			);

	void update(float dt) override;

	float getCenterY() const;

	sf::FloatRect getBounds() const;
	void setPosition(const sf::Vector2f& pos);

protected:
	sf::Drawable& getDrawable() override { return mShape; }

private:
    sf::RectangleShape               mShape;
    std::unique_ptr<ControlStrategy> mControlStrategy;
    float                            mSpeed;
};
