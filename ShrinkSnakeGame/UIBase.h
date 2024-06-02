#pragma once
#include <SFML/Graphics.hpp>

class Game;

class UIBase
{
public:
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& nowWindow) = 0;
	virtual void handleInput(sf::RenderWindow& nowWindow, sf::Event event) = 0;
	virtual void init() = 0;
	void setCursorType(sf::RenderWindow& nowWindow, sf::Cursor::Type type);
	~UIBase();
protected:
	Game* nowGame;
};