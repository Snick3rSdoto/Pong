#include "ScoreDisplay.hpp"
#include <string>

ScoreDisplay::ScoreDisplay(sf::RenderWindow& window,
                           const sf::Font& font,
                           const int& playerScore,
                           const int& opponentScore)
    : GameObject(window)
    , mPlayerScore(playerScore)
    , mOpponentScore(opponentScore)
{
    mText.setFont(font);
    mText.setCharacterSize(30);
    mText.setFillColor(sf::Color::White);

	mBackground.setFillColor(sf::Color(0, 0, 0, 0));

	setSize({200.f, 50.f});

	setPosition(WINDOW_WIDTH / 2.f - 100.f, 10.f);

	setDirection({0.f, 0.f});
	setSpeed(0.f);
}



void ScoreDisplay::update(float /*dt*/) {
    mText.setString(
        std::to_string(mPlayerScore) + " : " + std::to_string(mOpponentScore)
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

void ScoreDisplay::draw() {
    // Если хочешь фон – раскомментируй:
    // mWindow.draw(mBackground);

    mWindow.draw(mText);
}

void ScoreDisplay::setSize(const sf::Vector2f& size) {
    mBackground.setSize(size);
}

sf::Vector2f ScoreDisplay::getCenter() const {
    sf::Vector2f pos  = getPosition();
    sf::Vector2f size = mBackground.getSize();
    return { pos.x + size.x / 2.f, pos.y + size.y / 2.f };
}
