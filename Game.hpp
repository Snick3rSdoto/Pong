#pragma once
#include "Ball.hpp"

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
};
