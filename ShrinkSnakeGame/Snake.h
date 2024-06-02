#pragma once
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Map.h"
#include "CollisionInfo.h"
#include <SFML/Audio/Music.hpp>

class GameMenu;
class Tips;

class Snake : public Actor
{
public:
	Snake(sf::RenderWindow& nowWindow);
	~Snake();
	sf::Texture texSnake;
	sf::Sprite snake;
	sf::Texture texSnakeBody;
	sf::Sprite snakeBody;
	sf::Sprite snakeTailFlash;

	sf::Vector2f position;
	sf::Vector2i dir;

	mapPosition initPos;
	Map* envir;
public:
	void init(Map* nowMap);
	void setUpUItoSnake(GameMenu* ui);
	void render(sf::RenderWindow& nowWindow) override;
	void update() override;
	void handleInput(sf::RenderWindow& nowWindow, sf::Event event) override;
	void ChangeDirection(sf::Vector2i newDirection);
	void moveOneUnit();

	//a smaller, snake move faster
	void setMoveInterval(float a);
	CollisionInfo checkMapCollision();
	CollisionInfo checkSelfCollision();
	CollisionInfo checkItemCollision();

	bool addBodyToTail();
	bool removeBodyFromTail();

	//when you interact some items, like eat food, the snake tail maybe flash
	void flashSelf();
	void beginFlash();

	void flashSelfAll();
	void beginFlashAll();

	//if speedTime == 0 it means endless speed, speedTime is seconds
	void speedUp(float oneUnitInterval, float speedTime);

	void setCanMove(bool var);
	//Snake is ready to die
	void beginDie();
	void beginDieNotify();

	void addTipsToList(Tips* tip);
	void deleteTipFromList(Tips* tip);

	//Change game state
	void changeGamePause(bool isGameStop);

	bool getIsDied();

private:
	struct SnakeBody {
		mapPosition position;
		mapPosition lastposition;
		SnakeBody* prev;
		SnakeBody* next;
	};
	SnakeBody* head; // 蛇头节点
	SnakeBody* tail; // 蛇尾节点

	float initmoveUnitInterval = 0.2f;
	float nowmoveUnitInterval = 0.2f;
	sf::Clock clock;
	sf::Music died;
	bool isTailFlash = false;
	bool canMove = true;
	bool isDied = false;

	void endSpeedUp(float speedTime);

	GameMenu* nowUI;

	std::vector<Tips*> tipList;
};

