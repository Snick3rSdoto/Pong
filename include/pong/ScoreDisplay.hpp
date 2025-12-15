#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Config.hpp"

class ScoreDisplay : public StaticGameObject {
public:
    ScoreDisplay(sf::RenderWindow& window,
                 const sf::Font& font,
                 const int& playerScore,
                 const int& opponentScore);

    void update(float dt) override;

protected:
    sf::Drawable& getDrawable() override { return mText; }

private:
    sf::Text   mText;
    const int& mPlayerScore;
    const int& mOpponentScore;
};

