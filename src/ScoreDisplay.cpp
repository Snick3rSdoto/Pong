#include "ScoreDisplay.hpp"
#include <string>

ScoreDisplay::ScoreDisplay(sf::RenderWindow& window, const sf::Font& font)
	: GameObject(window)
{
    mText.setFont(font);
    mText.setCharacterSize(32);
    mText.setFillColor(sf::Color::White);

	mBackground.setFillColor(sf::Color(0, 0, 0, 0));

	setSize({200.f, 50.f});

	setPosition(WINDOW_WIDTH / 2.f - 100.f, 10.f);

	setDirection({0.f, 0.f});
	setSpeed(0.f);

	updateText();
}


void ScoreDisplay::update(float /*dt*/) {}


void ScoreDisplay::draw() {
    mWindow.draw(mText);
}

void ScoreDisplay::setSize(const sf::Vector2f& size) {
    mBackground.setSize(size);
	updateText();
}

sf::Vector2f ScoreDisplay::getCenter() const {
    sf::Vector2f pos  = getPosition();
    sf::Vector2f size = mBackground.getSize();
    return { pos.x + size.x / 2.f, pos.y + size.y / 2.f };
}

void ScoreDisplay::increment(ScoreOwner owner) {
    if (owner == ScoreOwner::Player)
        ++mPlayerScore;
    else
        ++mAiScore;

    updateText();
}

void ScoreDisplay::resetScores() {
    mPlayerScore = 0;
    mAiScore     = 0;
    updateText();
}

void ScoreDisplay::updateText() {
    mText.setString(
        std::to_string(mPlayerScore) + " : " + std::to_string(mAiScore)
    );

    sf::FloatRect textBounds = mText.getLocalBounds();
    sf::Vector2f  pos        = getPosition();
    sf::Vector2f  size       = mBackground.getSize();

    mText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    mText.setPosition(
        pos.x + size.x / 2.f,
        pos.y + size.y / 2.f
    );
}
