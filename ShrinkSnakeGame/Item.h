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
		// ʹ�õ�ǰʱ����Ϊ���������
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// ��ȡö�����͵ĵײ���������
		using UnderlyingType = typename std::underlying_type<ItemType>::type;

		// ���� 0 �� (max ֵ) ֮����������,��Ӧ ItemType ö�ٵĳ�Ա
		UnderlyingType randomIndex = static_cast<UnderlyingType>(std::rand()) % (static_cast<UnderlyingType>(ItemType::Orange) + 1);

		// ��������������ض�Ӧ�� ItemType ö��ֵ
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

