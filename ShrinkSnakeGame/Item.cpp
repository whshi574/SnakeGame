#include "Item.h"
#include <iostream>
#include "Snake.h"

void Item::loadFromFile(const std::string& filename)
{
	if (tex.loadFromFile(filename))
	{
		sprite.setTexture(tex);

		//Set image middle
		sf::FloatRect textBounds = sprite.getLocalBounds();
		sprite.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	}
	else
	{
		std::cout << "load item sprite faily" << std::endl;
	}
}

Item::Item(ItemType type, Map& nowMap, mapPosition initPos)
{
	envir = &nowMap;
	nowPos = initPos;
	nowType = type;
	//Set image info by type
	switch (nowType)
	{
	case Graph:
		setItemScore(5);
		loadFromFile("Content\\images\\Graph.png");
		break;
	case Orange:
		setItemScore(10);
		loadFromFile("Content\\images\\Orange.png");
		break;
	case Apple:
		setItemScore(15);
		loadFromFile("Content\\images\\Apple.png");
		break;
	default:
		break;
	}

	sprite.setPosition(nowMap.GetTileLoc(nowPos));

	eatFood.setVolume(100.0f);
	eatFood.openFromFile("Content\\music\\EatFood.mp3");
}

void Item::render(sf::RenderWindow& nowWindow)
{
	nowWindow.draw(sprite);
}

void Item::update()
{
}

void Item::handleInput(sf::RenderWindow& nowWindow, sf::Event event)
{
}

void Item::effect()
{
	switch (nowType)
	{
	case Graph:
		playEatMusic();
		envir->getPlayer()->addBodyToTail();
		envir->getPlayer()->flashSelf();
		break;
	case Apple:
		playEatMusic();
		envir->getPlayer()->addBodyToTail();
		envir->getPlayer()->speedUp(0.1f, 5.f);
		envir->getPlayer()->flashSelf();
		break;
	case Orange:
		playEatMusic();
		envir->getPlayer()->addBodyToTail();
		envir->getPlayer()->speedUp(0.3f, 5.f);
		envir->getPlayer()->flashSelf();
		break;
	default:
		break;
	}
}

mapPosition Item::getNowMapPos()
{
	return nowPos;
}

void Item::playEatMusic()
{
	eatFood.play();
}

int Item::getItemScore()
{
	return score;
}

void Item::setItemScore(int newScore)
{
	score = newScore;
}