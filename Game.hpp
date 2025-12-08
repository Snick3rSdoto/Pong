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
    void update(sf::Time dt);
    void render();

private:
    sf::RenderWindow mWindow;
	Ball			 mBall;
	Paddle			 mPaddle;
};
