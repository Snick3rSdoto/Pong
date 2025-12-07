#include <iostream>
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    sf::RenderWindow mWindow;
};


Game::Game()
: mWindow(sf::VideoMode(800, 600), "SFML Game")
{
}

void Game::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }

        //if (event.type == sf::Event::KeyPressed &&
            //event.key.code == sf::Keyboard::Escape) {
            //mWindow.close();
        //}
    }
}

void Game::update() {
}

void Game::render() {
    mWindow.display();
}


int main() {
    Game game;
    game.run();
    return 0;
}

