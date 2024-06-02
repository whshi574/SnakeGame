#pragma once
#include <SFML/Graphics.hpp>
class Actor
{
public:
	virtual void render(sf::RenderWindow& nowWindow) = 0;
	virtual void update() = 0;
	virtual void handleInput(sf::RenderWindow& nowWindow, sf::Event event) = 0;
};