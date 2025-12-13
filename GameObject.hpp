#pragma once 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class GameObject {
public:

	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual ~GameObject() = default;
};
