#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"
#include "Config.hpp"

class CenterLine : public GameObject {
public:
    explicit CenterLine(sf::RenderWindow& window);

	void update(float dt) override;

	void setSize(const sf::Vector2f& size) override;
	sf::Vector2f getCenter() const override;

protected:
	sf::Shape& getShape() override { return mShape; }
	const sf::Shape& getShape() const override { return mShape; }

private:
    sf::RectangleShape mShape;
};

