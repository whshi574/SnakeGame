#include "LoadMenu.h"
#include <iostream>
#include <thread>

LoadMenu::LoadMenu(sf::RenderWindow& nowWindow, Game* game, std::shared_ptr<UIBase> next)
{
	//Get game address
	nowGame = game;

	//Get now window information
	sf::Vector2u windowSize = nowWindow.getSize();

	//Start menu UI text init
	text.loadFromFile("Content\\font\\StartMenuButton.ttf");

	if (texSnake.loadFromFile("Content\\images\\SnakeHead.png")) {
		// 创建精灵并设置纹理
		snake.setTexture(texSnake);
		snake.setOrigin(snake.getGlobalBounds().width / 2.f, snake.getGlobalBounds().height / 2.f);
	}
	else {
		// 加载失败的处理
		std::cout << "Warning" << std::endl;
	}
	
	//Set Load UI text info
	load.setFont(text);
	load.setFillColor(sf::Color::White);
	load.setString("Loading");
	load.setCharacterSize(45);
	sf::FloatRect textBounds = load.getLocalBounds();
	load.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	load.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 20.f);
	snake.setScale(0.8f, 0.8f);

	//Load animaition
	
}

void LoadMenu::init()
{
}

void LoadMenu::update()
{
	
}

void LoadMenu::render(sf::RenderWindow& nowWindow)
{
	nowWindow.draw(load);
	nowWindow.draw(snake);
}

void LoadMenu::handleInput(sf::RenderWindow& nowWindow, sf::Event event)
{

}

void LoadMenu::loadAnimation()
{
	sf::Vector2f startpos;
	sf::Vector2f endPos;
	sf::Clock c;

	startpos.x = load.getGlobalBounds().left;
	startpos.y = load.getGlobalBounds().top + load.getGlobalBounds().height + 20.f;
	endPos.x = load.getGlobalBounds().left + load.getGlobalBounds().width;

	snake.setPosition(startpos);
	snake.setRotation(90.f);

	while (1) {
		if ((c.getElapsedTime().asSeconds() >= 1.f) && (isReadyInNextUI))
			break;
		//
		if (snake.getPosition().x >= endPos.x) 
		{
			snake.setPosition(startpos);
		}
		std::this_thread::sleep_for(std::chrono::nanoseconds(550));
		snake.setPosition(snake.getPosition().x + 0.03f, snake.getPosition().y);
	}

}