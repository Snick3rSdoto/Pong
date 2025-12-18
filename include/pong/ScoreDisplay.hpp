#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"
#include "Config.hpp"

class ScoreDisplay : public GameObject {
public:
    ScoreDisplay(sf::RenderWindow& window,
                 const sf::Font& font,
                 const int& playerScore,
                 const int& opponentScore);

    void update(float dt) override;
	void draw() override;

	void setSize(const sf::Vector2f& size) override;
	sf::Vector2f getCenter() const override;

protected:
	sf::Shape& getShape() override 	{ return mBackground; }
	const sf::Shape& getShape() const override { return mBackground; }

private:
	sf::RectangleShape 	mBackground;
    sf::Text   			mText;
    const int& 			mPlayerScore;
    const int& 			mOpponentScore;
};

