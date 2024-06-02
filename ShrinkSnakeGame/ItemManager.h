#pragma once
#include "Item.h"

class ItemManager
{
private:
	std::vector<Item*> itemList;
	Map* nowMap;
public:
	ItemManager(Map& now_Map);
	~ItemManager();
	//specific location
	void addItemToMap(ItemType type, mapPosition itemPos);
	//random location
	void addItemToMap(ItemType type);

	void removeItem(Item* item);

	void useItem(Item* item);
	//Render all item
	void renderAll(sf::RenderWindow& nowWindow);

	std::vector<Item*> getAllItem();
};

