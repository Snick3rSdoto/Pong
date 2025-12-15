#include "ScoreDisplay.hpp"
#include <string>

ScoreDisplay::ScoreDisplay(sf::RenderWindow& window,
                           const sf::Font& font,
                           const int& playerScore,
                           const int& opponentScore)
    : StaticGameObject(window)
    , mText()
    , mPlayerScore(playerScore)
    , mOpponentScore(opponentScore)
{
    mText.setFont(font);
    mText.setCharacterSize(30);
    mText.setFillColor(sf::Color::White);
}

void ScoreDisplay::update(float /*dt*/) {
    mText.setString(
        std::to_string(mPlayerScore) + " : " + std::to_string(mOpponentScore)
    );

    sf::FloatRect bounds = mText.getLocalBounds();
    mText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    mText.setPosition(WINDOW_WIDTH / 2.f, 30.f);
}

