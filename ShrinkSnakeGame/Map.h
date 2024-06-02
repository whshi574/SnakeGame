#pragma once
#include "Actor.h"
#include <SFML/Graphics.hpp>

class ItemManager;
class Snake;

struct mapPosition {
	unsigned int width;
	unsigned int height;

	// Ĭ�Ϲ��캯��
	mapPosition() : width(0), height(0) {}

	// ���ι��캯��
	mapPosition(unsigned int w, unsigned int h) : width(w), height(h) {}

	// ���� operator==�������ж����� mapPosition �Ƿ����
	bool operator==(const mapPosition& other) const {
		return width == other.width && height == other.height;
	}
};

class Map : public Actor, public sf::Drawable, public sf::Transformable
{
private:
	int CELL_SIZE = 20;
	int GRID_SIZE_X;
	int GRID_SIZE_Y;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	sf::Texture m_BG;
	sf::Sprite BG;

	//Map texture data, like stone , border, grass or others
	//0 it means nothing
	//1 it means purple block
	//2 it means red block
	//3 it means green block
	int* mapData;

	//Map position data, like the first tile pixcel position data
	std::vector<sf::Vector2f> mapPosData;

	ItemManager* itemManager;
	bool canCreateObstacle(double probability);

	//Player snake
	Snake* nowPlayer;
public:
	Map(sf::RenderWindow& nowWindow);
	~Map();
	//init manully
	void init(sf::RenderWindow& nowWindow);
	void render(sf::RenderWindow& nowWindow) override;
	void update() override;
	void handleInput(sf::RenderWindow& nowWindow, sf::Event event) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	sf::Vector2f GetTileLoc(unsigned int width, unsigned int height);
	sf::Vector2f GetTileLoc(mapPosition loc);
	mapPosition getRandomSpaceLoc();
	int getMapData(mapPosition loc);
	ItemManager& getItemManager();
	void setPlayer(Snake* player);
	Snake* getPlayer();
};

