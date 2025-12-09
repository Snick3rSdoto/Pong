#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"
#include <vector>
#include <memory>


class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

	void handleCollisions();
	void resetRound(int direction);

private:
    sf::RenderWindow mWindow;

    std::vector<std::shared_ptr<GameObject>> mObjects;
	std::shared_ptr<Ball>   mBall;
    std::shared_ptr<Paddle> mPlayerPaddle;
    std::shared_ptr<Paddle> mOpponentPaddle;

	int mPlayerScore{0};
	int mOpponentScore{0};

	sf::Font mFont;
	sf::Text mScoreText;
};
