#pragma once
#include "UIBase.h"

class LoadMenu : public UIBase
{
public:
	sf::Font text;
	sf::Text load;
	sf::Texture texSnake;
	sf::Sprite snake;
public:
	LoadMenu(sf::RenderWindow& nowWindow, Game* game, std::shared_ptr<UIBase> next);
	void init() override;
	void update() override;
	void render(sf::RenderWindow& nowWindow) override;
	void handleInput(sf::RenderWindow& nowWindow, sf::Event event) override;

private:
	bool isReadyInNextUI = false;
private:
	void loadAnimation();
};

