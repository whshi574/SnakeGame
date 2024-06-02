#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Map.h"

class SnakeBody :
    public Actor
{
private:
	mapPosition nowBodyPos;
	mapPosition lastBodyPos;
public:
	sf::Texture texSnake;
	sf::Sprite snake;
public:
	SnakeBody();
	void render(sf::RenderWindow& nowWindow) override;
	void update() override;
	void handleInput(sf::RenderWindow& nowWindow, sf::Event event) override;
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);

	void flashSelf();
	void beginFlash();
};