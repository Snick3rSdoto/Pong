#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "ScoreDisplay.hpp"
#include "CenterLine.hpp"
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

    bool handleGoalCollisions();
    void handlePaddleCollisions();
    void handlePaddleCollision(const std::shared_ptr<Paddle>& paddle, bool isLeftPaddle);

	void resetRound(int direction);

	void initObjects();

private:
    sf::RenderWindow mWindow;

    sf::Font mFont;

    std::shared_ptr<Ball>         mBall;
    std::shared_ptr<Paddle>       mPlayerPaddle;
    std::shared_ptr<Paddle>       mOpponentPaddle;
    std::shared_ptr<ScoreDisplay> mScoreDisplay;
    std::shared_ptr<CenterLine>   mCenterLine;

    std::vector<std::shared_ptr<GameObject>> mObjects;
};
