#include "ItemManager.h"

ItemManager::ItemManager(Map& now_Map)
{
	nowMap = &now_Map;
}

ItemManager::~ItemManager()
{
	for (Item* item : itemList)
	{
		if (item == nullptr)
			continue;
		delete item;
	}
	itemList.clear();
}

void ItemManager::addItemToMap(ItemType type, mapPosition itemPos)
{
	Item* newItem = new Item(type, *nowMap, itemPos);
	itemList.push_back(newItem);
}

void ItemManager::addItemToMap(ItemType type)
{
	Item* newItem = new Item(type, *nowMap, nowMap->getRandomSpaceLoc());
	itemList.push_back(newItem);
}

void ItemManager::removeItem(Item* item)
{
	if (!item)
		return;
	// ʹ�� std::find ����Ҫɾ����Ԫ�ص�λ��
	auto it = std::find(itemList.begin(), itemList.end(), item);
	if (it != itemList.end()) { // ����ҵ���
		itemList.erase(it); // ʹ�� erase ɾ��Ԫ��
		return;
	}

	//Not find item in item manager, delete it forclly
	delete item;
	return;
}

void ItemManager::useItem(Item* item)
{
	if (!item)
		return;

	item->effect();
	removeItem(item);
}

void ItemManager::renderAll(sf::RenderWindow& nowWindow)
{
	for (Item* item : itemList) {
		// ��ÿ�� item ���в���
		item->render(nowWindow);
	}
}

std::vector<Item*> ItemManager::getAllItem()
{
	return itemList;
}
