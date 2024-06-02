#pragma once
#include "UIBase.h"
#include "Snake.h"
#include "Map.h"
#include <Memory>
#include <SFML/Audio/Music.hpp>
#include "ItemManager.h"
#include "GameState.h"


class GameMenu : public UIBase
{
public:
	sf::Font text;
	sf::Text score;
	sf::Text scoreContent;
	sf::Music gameLoop;
	sf::Music buttonHover;

public:
	GameMenu(sf::RenderWindow& nowWindow, Game* game);
	~GameMenu();
	void init() override;
	void update() override;
	void render(sf::RenderWindow& nowWindow) override;
	void handleInput(sf::RenderWindow& nowWindow, sf::Event event) override;
	void addScore(int delta);
	void freshScore();
	//void changeState(GameState nextState);
	void GamingToPause();
	void PauseToGaming();

	void openPauseUI();
	void closePauseUI();
	void openPauseUIAnim();
	void closePauseUIAnim();
	void setIsGameOver(bool isGameOverVar);
	void openGGUI();
	void openGGUIAnim();

	void bindInteractButton(sf::Sprite& nowSprite, bool& isHover, void (*hover)(sf::Sprite&), void(*unHover)(sf::Sprite&));

private:
	GameState nowState;
	std::unique_ptr<Snake> player;
	//Maybe need delete mannully
	Map* envir;

	sf::Texture texStop;
	sf::Sprite spriteStop;

	sf::Texture texSandClock;
	sf::Sprite spriteSandClock;

	sf::Texture texSmallPanelBG;
	sf::Sprite spriteSmallPanelBG;

	sf::Texture texGamePauseBG;
	sf::Sprite spriteGamePauseBG;
	bool hoverStop = false;

	sf::Texture texContinueIcon;
	sf::Sprite spriteContinueIcon;
	bool hoverContinue = false;

	sf::Texture texRestartIcon;
	sf::Sprite spriteRestartIcon;
	bool hoverRestart = false;

	sf::Texture texHomeIcon;
	sf::Sprite spriteHomeIcon;
	bool hoverHome = false;

	sf::Text highestScoreTitle;
	sf::Text highestScoreCont;
	sf::Text gameOverTitle;
	sf::Text gameOverScore;

	bool isGamePause = false;
	bool isGameOver = false;
	bool canShowGameOver = false;
	bool canInteractGameOver = false;

	void beginPlayGameLoopMusic();

	int nowScore = 0;
};