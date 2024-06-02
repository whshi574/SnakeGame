#include "Map.h"
#include <iostream>
#include <random> // 包含随机数生成器的头文件
#include "ItemManager.h"
#include "Snake.h"

Map::Map(sf::RenderWindow& nowWindow)
{
	//Set cell info
    if (!m_BG.loadFromFile("Content\\images\\GameMenuBG.png")) {
        std::cout << "Load game menu bg failed" << std::endl;
    }
    else {
        BG.setTexture(m_BG);
    }

    GRID_SIZE_X = nowWindow.getSize().x / CELL_SIZE;
    GRID_SIZE_Y = nowWindow.getSize().y / CELL_SIZE;

    //mapdata init
    mapData = new int[GRID_SIZE_X * GRID_SIZE_Y];

    // 初始化随机数生成器
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    double probability = 0.05; // 概率

    for (int x = 0; x < GRID_SIZE_X; ++x) {
        for (int y = 0; y < GRID_SIZE_Y; ++y) {
            // 在这里调用填充地图块数据的函数，可以根据需要传入不同的参数
            if ((x == 0) || (x == 1) || (x == 2) || (x == 3) || (x == GRID_SIZE_X - 1) || (x == GRID_SIZE_X - 2) || (x == GRID_SIZE_X - 3) || (x == GRID_SIZE_X - 4)) {
                mapData[x + y * GRID_SIZE_X] = 1;
                continue;
            }

            if ((y == 0) || (y == 1) || (y == 2) || (y == 3) || (y == GRID_SIZE_Y - 1) || (y == GRID_SIZE_Y - 2) || (y == GRID_SIZE_Y - 3) || (y == GRID_SIZE_Y - 4)) {
                mapData[x + y * GRID_SIZE_X] = 1;
                continue;
            }
            mapData[x + y * GRID_SIZE_X] = canCreateObstacle(probability);
        }
    }

    load("Content\\images\\MapTileset.png", sf::Vector2u(20, 20), mapData, GRID_SIZE_X, GRID_SIZE_Y);

    itemManager = new ItemManager(*this);
    itemManager->addItemToMap(ItemType::Graph);
    itemManager->addItemToMap(ItemType::Apple);
    itemManager->addItemToMap(ItemType::Orange);
}

Map::~Map()
{
    //Todo
    delete itemManager;
    delete[] mapData;
}

void Map::init(sf::RenderWindow& nowWindow)
{
	
}

void Map::render(sf::RenderWindow& nowWindow)
{
    nowWindow.draw(*this);
}

void Map::update()
{
}

void Map::handleInput(sf::RenderWindow& nowWindow, sf::Event event)
{
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    target.draw(BG, states);
    // draw the vertex array
    target.draw(m_vertices, states);
}

bool Map::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int j = 0; j < height; ++j)
        for (unsigned int i = 0; i < width; ++i)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            mapPosData.push_back(sf::Vector2f(quad[0].position.x + (quad[1].position.x - quad[0].position.x) / 2, quad[1].position.y + (quad[2].position.y - quad[1].position.y) / 2));

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

sf::Vector2f Map::GetTileLoc(unsigned int width, unsigned int height)
{
    if ((width > GRID_SIZE_X) || (height > GRID_SIZE_Y)) 
    {
        return sf::Vector2f(0,0);
    }

    return mapPosData[width + height* GRID_SIZE_X];
}

mapPosition Map::getRandomSpaceLoc()
{
    bool isFind = false;
    mapPosition random;

    // 生成随机数种子
    std::random_device rd;
    std::mt19937 gen(rd());

    // 定义随机数分布，范围为 [0, gridSizeX) 和 [0, gridSizeY)
    std::uniform_int_distribution<int> disX(0, GRID_SIZE_X - 1);
    std::uniform_int_distribution<int> disY(0, GRID_SIZE_Y - 1);

    while (!isFind) 
    {
        // 生成随机的 x 和 y 坐标
        int randomX = disX(gen);
        int randomY = disY(gen);

        // 将 x 和 y 坐标转换成一个唯一的整数
        int randomInt = randomX + randomY * GRID_SIZE_X;

        if (mapData[randomInt] == 0) 
        {
            random.width = randomX;
            random.height = randomY;
            isFind = true;
            break;
        }
    }

    return random;
}

int Map::getMapData(mapPosition loc)
{
    if ((loc.width >= GRID_SIZE_X) || (loc.height >= GRID_SIZE_Y)) {
        return 0;
    }

    return mapData[loc.width + loc.height * GRID_SIZE_X];
}

ItemManager& Map::getItemManager()
{
    return *itemManager;
}

void Map::setPlayer(Snake* player)
{
    if (player == nullptr) {
        std::cout << "Warning, you set map player's pointer is nullptr" << std::endl;
        return;
    }

    nowPlayer = player;
}

Snake* Map::getPlayer()
{
    return nowPlayer;
}

bool Map::canCreateObstacle(double probability)
{
    double randomValue = static_cast<double>(std::rand()) / RAND_MAX;
    return randomValue < probability;
}

sf::Vector2f Map::GetTileLoc(mapPosition loc)
{
    if ((loc.width > GRID_SIZE_X) || (loc.height > GRID_SIZE_Y))
    {
        return sf::Vector2f(0, 0);
    }

    return mapPosData[loc.width + loc.height * GRID_SIZE_X];
}