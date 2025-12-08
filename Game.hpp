#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Paddle.hpp"


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
	int mPlayerScore{0};
	int mOpponentScore{0};

    sf::RenderWindow mWindow;
	Ball			 mBall;
	Paddle			 mPlayerPaddle;
	Paddle			 mOpponentPaddle;
};
