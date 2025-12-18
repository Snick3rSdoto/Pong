#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class GameObject {
public:
	explicit GameObject(sf::RenderWindow& window)
		: mWindow(window) {}

    virtual ~GameObject() = default;

    virtual void update(float dt) {
		sf::Vector2f pos = getPosition();
		sf::Vector2f velocity = mDirection * (mSpeed * dt);
		pos += velocity;
		setPosition(pos);
	}

    virtual void draw() {
		mWindow.draw(getShape());
	}

	void setPosition(float x, float y) {
		getShape().setPosition(x,y);
	}

	void setPosition(const sf::Vector2f& pos) {
		getShape().setPosition(pos);
	}

	sf::Vector2f getPosition() const {
		return getShape().getPosition();
	}


	void setDirection(const  sf::Vector2f& dir) {
		mDirection = dir;
	}

	sf::Vector2f getDirection() const {
		return mDirection;
	}


	void setSpeed(float speed) {
		mSpeed = speed;
	}

	float getSpeed() {
		return mSpeed;
	}


	void setColor(const sf::Color& color) {
		getShape().setFillColor(color);
	}

	virtual void setSize(const sf::Vector2f& size) = 0;

	virtual sf::Vector2f getCenter() const = 0;

	sf::FloatRect getBounds() const {
		return getShape().getGlobalBounds();
	}

protected:
	virtual sf::Shape& getShape() = 0;
	virtual const sf::Shape& getShape() const = 0;


protected:
	sf::RenderWindow&	mWindow;
	sf::Vector2f		mDirection{0.f, 0.f};
	float 				mSpeed{0.f};
};
