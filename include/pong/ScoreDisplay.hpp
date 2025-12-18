#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"
#include "Config.hpp"

enum class ScoreOwner {
	Player,
	Ai
};

class ScoreDisplay : public GameObject {
public:
    ScoreDisplay(sf::RenderWindow& window, const sf::Font& font);

    void update(float dt) override;
	void draw() override;

	void setSize(const sf::Vector2f& size) override;
	sf::Vector2f getCenter() const override;

	void increment(ScoreOwner owner);
	void resetScores();

	int getPlayerScore() const  { return mPlayerScore; }
	int getAiScore() const      { return mAiScore; }

protected:
	sf::Shape& getShape() override 	{ return mBackground; }
	const sf::Shape& getShape() const override { return mBackground; }

private:
	void updateText();

	sf::RectangleShape 	mBackground;
    sf::Text   			mText;

	int mPlayerScore{0};
	int mAiScore{0};
};

