#pragma once
#include "Actor.h"
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <SFML/Audio/Music.hpp>

enum ItemType {
	Graph,
	Apple,
	Orange
};

namespace ItemTypeFunc {

	ItemType static getRandomItemType() {
		// 使用当前时间作为随机数种子
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// 获取枚举类型的底层整数类型
		using UnderlyingType = typename std::underlying_type<ItemType>::type;

		// 生成 0 到 (max 值) 之间的随机整数,对应 ItemType 枚举的成员
		UnderlyingType randomIndex = static_cast<UnderlyingType>(std::rand()) % (static_cast<UnderlyingType>(ItemType::Orange) + 1);

		// 根据随机索引返回对应的 ItemType 枚举值
		return static_cast<ItemType>(randomIndex);
	}
}

class Item : public Actor
{
private:
	mapPosition nowPos;

	sf::Texture tex;
	sf::Sprite sprite;

	sf::Music eatFood;

	ItemType nowType;
	void loadFromFile(const std::string& filename);
	Map* envir;

	int score;
public:
	Item(ItemType type, Map& nowMap, mapPosition initPos);
	void render(sf::RenderWindow& nowWindow) override;
	void update() override;
	void handleInput(sf::RenderWindow& nowWindow, sf::Event event) override;
	void effect();
	mapPosition getNowMapPos();
	void playEatMusic();
	int getItemScore();
	void setItemScore(int newScore);
};

