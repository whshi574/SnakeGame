#pragma once
#include "UIBase.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Music.hpp>

class StartMenu: public UIBase
{
public:
	sf::Font text;
	sf::Text title;
	sf::Text play;
	sf::Text scorelist;
	sf::Text exit;
	sf::Music menuLoop;
	sf::Music menuHover;
	std::string gameName = "Snake";
	sf::Texture texBg;
	sf::Sprite BG;
	sf::Texture titleBg;
	sf::Sprite titleBG;
	sf::Texture texScoreList;
	sf::Sprite scoreListBG;
	sf::Vector2f scoreListInitLoc;
	sf::Vector2f scoreListTarLoc;
	sf::Text scoreHighestTitle;
	sf::Vector2f scoreHighestTitleInitLoc;
	sf::Vector2f scoreHighestTitleTarLoc;
	sf::Text scoreHighest;
	sf::Vector2f scoreHighestInitLoc;
	sf::Vector2f scoreHighestTarLoc;
	sf::Text scoreRecentTitle;
	sf::Vector2f scoreRecentTitleInitLoc;
	sf::Vector2f scoreRecentTitleTarLoc;
	std::vector<sf::Text*> scoreRecent;
	sf::Vector2f scoreRecentInitLoc;
	sf::Vector2f scoreRecentTarLoc;


public:
	StartMenu(sf::RenderWindow& nowWindow, Game* game);
	~StartMenu();
	void init() override;
	void update() override;
	void render(sf::RenderWindow& nowWindow) override;
	void handleInput(sf::RenderWindow& nowWindow, sf::Event event) override;
	void openScoreList();
	void closeScoreList();

private:
	bool hoverPlay = false;
	bool hoverScorelist = false;
	bool hoverExit = false;
	bool scoreListAppear = false;
	bool scoreListIsClosing = false;
	bool scoreListIsOpening = false;

	void openScoreListAnim();
	void closeScoreListAnim();

	void readScore();
};