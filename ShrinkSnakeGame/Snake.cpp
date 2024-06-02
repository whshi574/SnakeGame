#include "Snake.h"
#include <iostream>
#include <cmath>
#include "ItemManager.h"
#include "GameMenu.h"
#include "Tips.h"

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif
#include <thread>

Snake::Snake(sf::RenderWindow& nowWindow)
{
	if (texSnake.loadFromFile("Content\\images\\SnakeHead.png")) {
		// 创建精灵并设置纹理
		snake.setTexture(texSnake);
		snake.setOrigin(snake.getGlobalBounds().width / 2.f, snake.getGlobalBounds().height / 2.f);
	}
	else {
		// 加载失败的处理
		std::cout << "Warning" << std::endl;
	}

	if (texSnakeBody.loadFromFile("Content\\images\\SnakeBody.png")) {
		// 创建精灵并设置纹理
		snakeBody.setTexture(texSnakeBody);
		snakeTailFlash.setTexture(texSnakeBody);
		snakeBody.setOrigin(snakeBody.getGlobalBounds().width / 2.f, snakeBody.getGlobalBounds().height / 2.f);
		snakeTailFlash.setOrigin(snakeBody.getGlobalBounds().width / 2.f, snakeBody.getGlobalBounds().height / 2.f);
	}
	else {
		// 加载失败的处理
		std::cout << "Warning" << std::endl;
	}

	snake.setOrigin(snake.getLocalBounds().width / 2.f, snake.getLocalBounds().height / 2.f);
	snakeBody.setOrigin(snake.getLocalBounds().width / 2.f, snake.getLocalBounds().height / 2.f);
	snakeTailFlash.setOrigin(snake.getLocalBounds().width / 2.f, snake.getLocalBounds().height / 2.f);

	initPos.height = 20;
	initPos.width = 20;


	head = new SnakeBody();
	head->position = initPos;/* 初始位置 */;
	head->prev = nullptr;
	head->next = nullptr;
	tail = head; // 初始化尾部节点为头部节点

	// 创建并链接五个身体节点
	for (int i = 0; i < 5; ++i) {
		addBodyToTail();
	}

	died.openFromFile("Content\\music\\die.mp3");
	died.setVolume(50.f);

}

bool Snake::addBodyToTail() {
	//Todo: maybe have length restriction
	if (head == nullptr) {
		return 0;
	}

	SnakeBody* newBodyPart = new SnakeBody();
	mapPosition initTempPos;
	initTempPos = tail->position;

	tail->next = newBodyPart;
	newBodyPart->prev = tail;
	newBodyPart->next = nullptr;
	//Todo + operator
	initTempPos.width -= dir.x;
	initTempPos.height -= dir.y;

	newBodyPart->position = initTempPos;
	newBodyPart->lastposition = initTempPos;

	tail = newBodyPart;
	return 1;
}

bool Snake::removeBodyFromTail()
{
	return false;
}

Snake::~Snake()
{
	// 释放 body 中的所有 SnakeBody 实例
	// 释放链表中的所有节点
	SnakeBody* current = head;
	while (current) {
		SnakeBody* next = current->next;
		delete current;
		current = next;
	}
}

void Snake::render(sf::RenderWindow& nowWindow)
{
	// 渲染贪吃蛇的身体
	if (envir == nullptr) {
		return;
	}

	SnakeBody* current = head;
	while (current) {
		if (current == head) {
			snake.setPosition(envir->GetTileLoc(current->position));
			nowWindow.draw(snake);
			current = current->next;
			continue;
		}
		
		if (current == tail) {
			if (isTailFlash) {
				snakeTailFlash.setPosition(envir->GetTileLoc(current->position));
				nowWindow.draw(snakeTailFlash);
			}
			else {
				snakeBody.setPosition(envir->GetTileLoc(current->position));
				nowWindow.draw(snakeBody);
			}
			current = current->next;
			continue;
		}
		
		snakeBody.setPosition(envir->GetTileLoc(current->position));
		nowWindow.draw(snakeBody);
		current = current->next;
	}
	
	for (Tips* nowTip : tipList) {
		if (nowTip == nullptr) {
			std::cout << "The tips pointer is removed ,but you dont delete the pointer from tipList" << std::endl;
			continue;
		}
		nowWindow.draw(*nowTip);
	}
}

void Snake::init(Map* nowMap)
{
	snake.setPosition(nowMap->GetTileLoc(initPos.width, initPos.height));
	ChangeDirection(sf::Vector2i(-1, 0));
	clock.restart();
	envir = nowMap;
}

void Snake::setUpUItoSnake(GameMenu* ui)
{
	if (ui == nullptr) {
		std::cout << "Warning, your snake dont have ui pointer" << std::endl;
		return;
	}
	nowUI = ui;
}

void Snake::update()
{
	if (!canMove)
		goto MoveEnd;
	if (clock.getElapsedTime().asSeconds() >= nowmoveUnitInterval) {
		// 每隔 moveInterval 秒移动一次蛇
		moveOneUnit();
		clock.restart(); // 重置时钟
	}
MoveEnd:
	return;
}

void Snake::handleInput(sf::RenderWindow& nowWindow, sf::Event event)
{
	if (!canMove)
		goto ChangeDirEnd;
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::W)
		{
			std::cout << "W key pressed!" << std::endl;
			if (dir == sf::Vector2i(0, -1)) {
				//It means the same direction for snake and player direction
				//moveOneUnit();
			}
			else {
				ChangeDirection(sf::Vector2i(0, -1));
				//moveOneUnit();
			}
		}
		if (event.key.code == sf::Keyboard::A)
		{
			std::cout << "A key pressed!" << std::endl;
			ChangeDirection(sf::Vector2i(-1, 0));
			//moveOneUnit();
		}
		if (event.key.code == sf::Keyboard::S)
		{
			std::cout << "S key pressed!" << std::endl;
			ChangeDirection(sf::Vector2i(0, 1));
			//moveOneUnit();
		}
		if (event.key.code == sf::Keyboard::D)
		{
			std::cout << "D key pressed!" << std::endl;
			ChangeDirection(sf::Vector2i(1, 0));
			//moveOneUnit();
		}
	}
ChangeDirEnd:
	return;
}

void Snake::ChangeDirection(sf::Vector2i newDirection)
{
	dir = newDirection;
	float angle = std::atan2(static_cast<float>(dir.y), static_cast<float>(dir.x));
	angle = angle * 180.0f / static_cast<float>(M_PI);
	angle += 90.f;
	std::cout << angle << std::endl;
	snake.setRotation(angle);
}

void Snake::moveOneUnit()
{
	head->lastposition = head->position;

	head->position.width += dir.x;
	head->position.height += dir.y;

	// 移动蛇身体的每个部分
	SnakeBody* current = head->next;
	while (current) {
		// 计算当前身体部分的移动方向
		current->lastposition = current->position;
		current->position = current->prev->lastposition;
		current = current->next;
	}

	if (checkMapCollision().collided == 1) {
		//Collision occurred
		std::cout << "Collosion map occurred" << std::endl;
		beginDie();
	}

	if (checkSelfCollision().collided == 1) {
		//Collision occurred
		std::cout << "Collosion self occurred" << std::endl;
		beginDie();
	}

	if (checkItemCollision().collided == 1) {
		//Collision occurred
		std::cout << "Collosion item occurred" << std::endl;

		Item* item = static_cast<Item*>(checkItemCollision().actor);
		if (item == nullptr)
			return;
		envir->getItemManager().useItem(item);
		if (nowUI == nullptr) {
			std::cout << "Warning, add score faily, because of nowUI in snake is nullptr" << std::endl;
			return;
		}
		nowUI->addScore(item->getItemScore());
		std::string tipCont;
		std::to_string(item->getItemScore());
		tipCont = "+" + std::to_string(item->getItemScore());
		Tips* tip = new Tips(tipCont, envir->GetTileLoc(head->position), [&](Tips* tip) { deleteTipFromList(tip); });
		addTipsToList(tip);
		envir->getItemManager().addItemToMap(ItemTypeFunc::getRandomItemType());
	}
}

void Snake::setMoveInterval(float a)
{
	if (a < 0.f)
		return;
	nowmoveUnitInterval = a;
}

CollisionInfo Snake::checkMapCollision()
{
	CollisionInfo info;
	info.collided = 0;
	if (envir == nullptr)
		return info;

	if (!envir->getMapData(head->position)) 
	{
		info.collided = 0;
		return info;
	}

	info.collided = 1;
	return info;
}

CollisionInfo Snake::checkSelfCollision()
{
	CollisionInfo info;
	info.collided = 0;
	
	// 如果蛇只有头节点，不会与身体碰撞
	if (head == nullptr || head->next == nullptr) {
		return info;
	}

	// 从头节点的下一个节点开始遍历蛇的身体
	SnakeBody* current = head->next;
	while (current != nullptr) {
		// 如果蛇头的位置与当前身体节点的位置重合，则有碰撞
		if (head->position.width == current->position.width && head->position.height == current->position.height) {
			info.collided = 1;
			return info;
		}
		current = current->next;
	}

	// 如果遍历完整个蛇的身体都没有重合，则无碰撞
	return info;
}

CollisionInfo Snake::checkItemCollision()
{
	CollisionInfo info;
	info.collided = 0;

	ItemManager& a = envir->getItemManager();

	for (Item* item : a.getAllItem()) {
		// 处理 item 指向的对象
		if (item->getNowMapPos() == (head->position)) {
			info.collided = 1;
			info.actor = item;
		}
	}

	return info;
}

void Snake::flashSelf() {
	std::thread t(&Snake::beginFlash, this);
	t.detach();
}

void Snake::beginFlash() {
	sf::Clock clock;
	isTailFlash = true;
	auto start = std::chrono::high_resolution_clock::now();

	while (clock.getElapsedTime().asSeconds() <= 2.0f) 
	{
		// 计算经过的时间(秒)
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(now - start).count();

		// 计算当前 alpha 值
		float alpha = std::fabs(std::sin(duration * 0.8f * 3.14159f)); // 0 到 1 的循环变化

		snakeTailFlash.setColor(sf::Color(static_cast<sf::Uint8>(alpha * 255), static_cast<sf::Uint8>(alpha * 255), static_cast<sf::Uint8>(alpha * 255), 255));
	}

	snakeTailFlash.setColor(sf::Color(255, 255, 255, 255));
	isTailFlash = false;
}

void Snake::flashSelfAll()
{
	std::thread t(&Snake::beginFlashAll, this);
	t.detach();
}

void Snake::beginFlashAll()
{
	sf::Clock clock;
	auto start = std::chrono::high_resolution_clock::now();
	sf::Color snakeColor = snake.getColor();
	sf::Color snakeBodyColor = snakeBody.getColor();

	while (clock.getElapsedTime().asSeconds() <= 3.0f)
	{
		// 计算经过的时间(秒)
		auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(now - start).count();

		// 计算当前 alpha 值
		float alpha = std::fabs(std::sin(duration * 0.8f * 3.14159f)); // 0 到 1 的循环变化

		if (&snakeBody == nullptr)
			return;
		snakeBody.setColor(sf::Color(snakeBodyColor.r, snakeBodyColor.g, snakeBodyColor.b, 255 * alpha));
		if (&snake == nullptr)
			return;
		snake.setColor(sf::Color(snakeColor.r, snakeColor.g, snakeColor.b, 255 * alpha));
	}
}

void Snake::speedUp(float oneUnitInterval, float speedTime)
{
	setMoveInterval(oneUnitInterval);

	if (!speedTime)
		return;
	std::thread t(&Snake::endSpeedUp, this, speedTime);
	t.detach();
}

void Snake::setCanMove(bool var)
{
	canMove = var;
}

void Snake::beginDie()
{
	isDied = true;
	setCanMove(false);
	flashSelfAll();
	died.play();
	nowUI->setIsGameOver(true);

	std::thread t(&Snake::beginDieNotify, this);
	t.detach();
}

void Snake::beginDieNotify()
{
	std::this_thread::sleep_for(std::chrono::seconds(3));

	if (nowUI == nullptr)
	{
		std::cout << "The now ui in snake is not set up correctly" << std::endl;
	}

	//悬空指针问题
	nowUI->openGGUI();
}

void Snake::addTipsToList(Tips* tip)
{
	if (tip == nullptr)
		return;
	tipList.push_back(tip);
}

void Snake::deleteTipFromList(Tips* tip)
{
	if (tip == nullptr || this == nullptr)
		return;

	// 遍历tipList查找要删除的指针
	for (auto it = tipList.begin(); it != tipList.end(); ++it) {
		if (*it == tip) {
			// 找到要删除的指针，使用erase函数删除
			tipList.erase(it);
			break; // 删除后退出循环
		}
	}

	delete tip;
}

void Snake::changeGamePause(bool isGameStop)
{
	if (isDied)
		return;
	if (isGameStop) 
	{
		setCanMove(false);
	}
	else 
	{
		setCanMove(true);
	}
}

bool Snake::getIsDied()
{
	return isDied;
}

void Snake::endSpeedUp(float speedTime)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(speedTime * 1000)));
	setMoveInterval(initmoveUnitInterval);
}
