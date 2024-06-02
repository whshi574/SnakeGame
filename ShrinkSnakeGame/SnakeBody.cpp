#include "SnakeBody.h"
#include <iostream>
#include <thread>

SnakeBody::SnakeBody()
{
	if (texSnake.loadFromFile("Content\\images\\SnakeBody.png")) {
		// �������鲢��������
		snake.setTexture(texSnake);
		snake.setOrigin(snake.getGlobalBounds().width / 2.f, snake.getGlobalBounds().height / 2.f);
	}
	else {
		// ����ʧ�ܵĴ���
		std::cout << "Warning" << std::endl;
	}
	//��ͼƬ���ж���
	snake.setOrigin(snake.getLocalBounds().width / 2.f, snake.getLocalBounds().height / 2.f);
}

void SnakeBody::render(sf::RenderWindow& nowWindow)
{
	nowWindow.draw(snake);
}

void SnakeBody::update()
{
}

void SnakeBody::handleInput(sf::RenderWindow& nowWindow, sf::Event event)
{
}

void SnakeBody::setPosition(const sf::Vector2f& position)
{
	snake.setPosition(position);
}

void SnakeBody::setPosition(float x, float y)
{
	snake.setPosition(x, y);
}

void SnakeBody::flashSelf() {
	std::thread t(&SnakeBody::beginFlash, this);
	t.detach();
}

void SnakeBody::beginFlash() {
	//
	while (1) {
		snake.setScale(0,0);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}