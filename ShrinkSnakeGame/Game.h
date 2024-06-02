#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class UIBase;

const double FrameRate = 60; // 期望的帧率
const double frameTime = 1.0 / FrameRate; // 每帧的时间间隔


class Game
{
private:
	sf::RenderWindow* mainWindow;
	std::string name = "ConstantlyShrinking!";
	std::shared_ptr<UIBase> currentUI;
	sf::Vector2u windowInitSize;
public:

protected:

private:

public:
	Game();
	~Game();
	void Render();
	void Update();
	void HandleInput();
	void runLoop();
	sf::RenderWindow* GetWindow();
	
	void changeUI(std::shared_ptr<UIBase> next);
protected:


};

