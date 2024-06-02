#include "StartMenu.h"
#include "GameMenu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include "Game.h"
#include "LoadMenu.h"
#include <thread>
#include <fstream>
#include <string>
#include "scoreManager.h"

StartMenu::StartMenu(sf::RenderWindow& nowWindow, Game* game)
{
	std::cout << "StartMenu constructor" << std::endl;
	//Get game address
	nowGame = game;

	//Get now window information
	sf::Vector2u windowSize = nowWindow.getSize();

	//Start menu UI text init
	text.loadFromFile("Content\\font\\StartMenuButton.ttf");

	sf::FloatRect textBounds = title.getLocalBounds();

/*	title.setFont(text);
	title.setFillColor(sf::Color::White);
	title.setString(gameName);
	title.setCharacterSize(70);
	title.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	title.setPosition(windowSize.x/2.f, windowSize.y / 2.f - 100.f);*/

	float buttonOffset = 500.f;

	play.setFont(text);
	play.setFillColor(sf::Color(0x7ED957ff));
	play.setString("Play");
	play.setCharacterSize(30);
	textBounds = play.getLocalBounds();
	play.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	play.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 1000.f);
	play.setOutlineThickness(2.f);
	play.setOutlineColor(sf::Color(0x5E17EBff));

	scorelist.setFont(text);
	scorelist.setFillColor(sf::Color(0xFFDE59ff));
	scorelist.setString("Score List");
	scorelist.setCharacterSize(30);
	textBounds = scorelist.getLocalBounds();
	scorelist.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	scorelist.setPosition(windowSize.x / 2.f, play.getPosition().y + buttonOffset);
	scorelist.setOutlineThickness(2.f);
	scorelist.setOutlineColor(sf::Color(0x5E17EBff));

	exit.setFont(text);
	exit.setFillColor(sf::Color(0xCD233Aff));
	exit.setString("Exit");
	exit.setCharacterSize(30);
	textBounds = exit.getLocalBounds();
	exit.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	exit.setPosition(windowSize.x / 2.f, scorelist.getPosition().y + buttonOffset);
	exit.setOutlineThickness(2.f);
	exit.setOutlineColor(sf::Color(0x5E17EBff));

	if (texBg.loadFromFile("Content\\images\\StartMenuBG.png")) {
		
		BG.setTexture(texBg);
	}
	else {
		// 加载失败的处理
		std::cout << "Warning" << std::endl;
	}

	if (titleBg.loadFromFile("Content\\images\\StartMenuBGTitle.png")) {
		titleBG.setTexture(titleBg);
	}
	else {
		// 加载失败的处理
		std::cout << "Warning" << std::endl;
	}

	if (texScoreList.loadFromFile("Content\\images\\scoreListBG.png")) {
		scoreListBG.setTexture(texScoreList);
	}
	else {
		// 加载失败的处理
		std::cout << "Warning" << std::endl;
	}


	sf::Text* score1 = new sf::Text();
	scoreRecent.push_back(score1);

	sf::Text* score2 = new sf::Text();
	scoreRecent.push_back(score2);

	sf::Text* score3 = new sf::Text();
	scoreRecent.push_back(score3);

	readScore();

	scoreListBG.setPosition(scoreListBG.getPosition().x, (windowSize.y - scoreListBG.getGlobalBounds().height));
	scoreListTarLoc = scoreListBG.getPosition();
	scoreListInitLoc.y = scoreListTarLoc.y + 50.f;

	scoreHighestTitle.setFont(text);
	scoreHighestTitle.setFillColor(sf::Color(0x5E17EBff));
	scoreHighestTitle.setString("The highest score");
	scoreHighestTitle.setCharacterSize(30);
	textBounds = scoreHighestTitle.getLocalBounds();
	scoreHighestTitle.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	scoreHighestTitle.setPosition(windowSize.x / 2.f, scoreListTarLoc.y + 140.f);
	scoreHighestTitle.setOutlineThickness(2.f);
	scoreHighestTitle.setOutlineColor(sf::Color(0x7ED957ff));
	scoreHighestTitleInitLoc = scoreHighestTitle.getPosition();
	scoreHighestTitleTarLoc.y = scoreHighestTitleInitLoc.y - 50.f;
	scoreHighestTitle.setFillColor(sf::Color(scoreHighestTitle.getFillColor().r, scoreHighestTitle.getFillColor().g, scoreHighestTitle.getFillColor().b, 0));
	scoreHighestTitle.setOutlineColor(sf::Color(scoreHighestTitle.getOutlineColor().r, scoreHighestTitle.getOutlineColor().g, scoreHighestTitle.getOutlineColor().b, 0));

	scoreHighest.setFont(text);
	scoreHighest.setFillColor(sf::Color::White);
	scoreHighest.setCharacterSize(30);
	textBounds = scoreHighest.getLocalBounds();
	scoreHighest.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	scoreHighest.setPosition(windowSize.x / 2.f, scoreListTarLoc.y + 190.f);
	scoreHighest.setOutlineThickness(2.f);
	scoreHighest.setOutlineColor(sf::Color(0x5E17EBff));
	scoreHighestInitLoc = scoreHighest.getPosition();
	scoreHighestTarLoc.y = scoreHighestInitLoc.y - 50.f;
	scoreHighest.setFillColor(sf::Color(scoreHighest.getFillColor().r, scoreHighest.getFillColor().g, scoreHighest.getFillColor().b, 0));
	scoreHighest.setOutlineColor(sf::Color(scoreHighest.getOutlineColor().r, scoreHighest.getOutlineColor().g, scoreHighest.getOutlineColor().b, 0));

	scoreRecentTitle.setFont(text);
	scoreRecentTitle.setFillColor(sf::Color(0x7ED957ff));
	scoreRecentTitle.setString("Recent Score");
	scoreRecentTitle.setCharacterSize(30);
	textBounds = scoreRecentTitle.getLocalBounds();
	scoreRecentTitle.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	scoreRecentTitle.setPosition(windowSize.x / 2.f, scoreListTarLoc.y + 260.f);
	scoreRecentTitle.setOutlineThickness(2.f);
	scoreRecentTitle.setOutlineColor(sf::Color(0x5E17EBff));
	scoreRecentTitleInitLoc = scoreRecentTitle.getPosition();
	scoreRecentTitleTarLoc.y = scoreRecentTitleInitLoc.y - 50.f;
	scoreRecentTitle.setFillColor(sf::Color(scoreRecentTitle.getFillColor().r, scoreRecentTitle.getFillColor().g, scoreRecentTitle.getFillColor().b, 0));
	scoreRecentTitle.setOutlineColor(sf::Color(scoreRecentTitle.getOutlineColor().r, scoreRecentTitle.getOutlineColor().g, scoreRecentTitle.getOutlineColor().b, 0));

	int count = 0;

	scoreRecentInitLoc.x = scoreRecentTitleInitLoc.x;
	scoreRecentInitLoc.y = scoreRecentTitleInitLoc.y + 50.f;
	scoreRecentTarLoc.x = scoreRecentTitleInitLoc.x;
	scoreRecentTarLoc.y = scoreRecentTitleInitLoc.y;

	for (sf::Text* nowText : scoreRecent)
	{
		nowText->setFont(text);
		nowText->setFillColor(sf::Color::White);
		//Remeber to delete
		nowText->setCharacterSize(30);
		textBounds = nowText->getLocalBounds();
		nowText->setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
		nowText->setPosition(windowSize.x / 2.f, scoreRecentInitLoc.y + 40.f * count);
		nowText->setFillColor(sf::Color(nowText->getFillColor().r, nowText->getFillColor().g, nowText->getFillColor().b, 0));
		nowText->setOutlineColor(sf::Color(nowText->getOutlineColor().r, nowText->getOutlineColor().g, nowText->getOutlineColor().b, 0));
		count++;
	}

	//Start menu UI music init
	menuLoop.setVolume(10.0f);
	menuLoop.openFromFile("Content\\music\\music_zapsplat_easy_cheesy.mp3");
	menuLoop.setLoop(true);
	menuHover.setVolume(500.0f);
	menuHover.openFromFile("Content\\music\\menu-screen-mouse-over.wav");
}

StartMenu::~StartMenu()
{
	//Delete something
	for (sf::Text* now : scoreRecent) 
	{
		delete now;
	}


	sf::Time duration = sf::seconds(1.0f);
	sf::Time elapsedTime;
	sf::Clock clock;

	float initVolume = menuLoop.getVolume();
	sf::Uint8 initA = title.getFillColor().a;
	sf::RenderWindow* nowWindow = nowGame->GetWindow();

	while (elapsedTime < duration) {
		//Fade out loop
		float fadeRatio = elapsedTime / duration;
		float volume = 1.0f - fadeRatio;

		menuLoop.setVolume(initVolume * volume);
		
		sf::Color color;
		play.setFillColor(sf::Color(play.getFillColor().r, play.getFillColor().g, play.getFillColor().b, 255 * volume));
		color = play.getOutlineColor();
		color.a = 255 * volume;
		play.setOutlineColor(color);

		scorelist.setFillColor(sf::Color(scorelist.getFillColor().r, scorelist.getFillColor().g, scorelist.getFillColor().b, 255 * volume));
		color = scorelist.getOutlineColor();
		color.a = 255 * volume;
		scorelist.setOutlineColor(color);

		exit.setFillColor(sf::Color(exit.getFillColor().r, exit.getFillColor().g, exit.getFillColor().b, 255 * volume));
		color = exit.getOutlineColor();
		color.a = 255 * volume;
		exit.setOutlineColor(color);

		BG.setColor(sf::Color(BG.getColor().r, BG.getColor().g, BG.getColor().b, 255 * volume));
		titleBG.setColor(sf::Color(titleBG.getColor().r, titleBG.getColor().g, titleBG.getColor().b, 255 * volume));
		
		nowWindow->clear();
		nowWindow->draw(BG);
		nowWindow->draw(titleBG);
		nowWindow->draw(play);
		nowWindow->draw(scorelist);
		nowWindow->draw(exit);
		nowWindow->display();

		elapsedTime = clock.getElapsedTime();
	}

	menuLoop.setVolume(0.0f);
}

void StartMenu::init()
{
	menuLoop.play();
}

void StartMenu::update()
{

}

void StartMenu::render(sf::RenderWindow& nowWindow)
{

	
	if (hoverPlay) {
		//Set the effect of play text when hover text
		float boundOffsetX = -5.f;
		float boundOffsetY = 5.f;

		sf::Vector2u windowSize = nowWindow.getSize();
		play.setPosition(windowSize.x / 2.f + boundOffsetX, windowSize.y / 2.f + 50.f - boundOffsetY);
	}
	else {
		sf::Vector2u windowSize = nowWindow.getSize();
		play.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 50.f);
	}

	if (hoverScorelist) {
		//Set the effect of play text when hover text
		float boundOffsetX = -5.f;
		float boundOffsetY = 5.f;

		sf::Vector2u windowSize = nowWindow.getSize();
		scorelist.setPosition(windowSize.x / 2.f + boundOffsetX, windowSize.y / 2.f + 100.f - boundOffsetY);
	}
	else {
		sf::Vector2u windowSize = nowWindow.getSize();
		scorelist.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 100.f);
	}

	if (hoverExit) {
		//Set the effect of play text when hover text
		float boundOffsetX = -5.f;
		float boundOffsetY = 5.f;

		sf::Vector2u windowSize = nowWindow.getSize();
		exit.setPosition(windowSize.x / 2.f + boundOffsetX, windowSize.y / 2.f + 150.f - boundOffsetY);
	}
	else {
		sf::Vector2u windowSize = nowWindow.getSize();
		exit.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 150.f);
	}

	nowWindow.draw(BG);
	nowWindow.draw(titleBG);
	nowWindow.draw(play);
	nowWindow.draw(scorelist);
	nowWindow.draw(exit);

	if (scoreListAppear) 
	{
		nowWindow.draw(scoreListBG);
		nowWindow.draw(scoreHighestTitle);
		nowWindow.draw(scoreHighest);
		nowWindow.draw(scoreRecentTitle);
		for (sf::Text* nowText : scoreRecent)
		{
			nowWindow.draw(*nowText);
		}
	}
}

void StartMenu::handleInput(sf::RenderWindow& nowWindow, sf::Event event)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(nowWindow);
	sf::Vector2f worldPosition = nowWindow.mapPixelToCoords(mousePosition);
	//std::cout << "PositionX: " << worldPosition.x << "PositionY: " << worldPosition.y << std::endl;
	if (scoreListAppear) {
		if (worldPosition.y <= scoreListBG.getPosition().y) {
			setCursorType(nowWindow, sf::Cursor::Hand);
		}
		else {
			setCursorType(nowWindow, sf::Cursor::Arrow);
		}
		goto IgnoreInteract;
	}

	if (play.getGlobalBounds().contains(worldPosition)) {
		if (!hoverPlay) {
			menuHover.play();
			setCursorType(nowWindow, sf::Cursor::Hand);
		}
		hoverPlay = true;
	}
	else {
		if (hoverPlay) {
			setCursorType(nowWindow, sf::Cursor::Arrow);
		}
		hoverPlay = false;
	}

	if (scorelist.getGlobalBounds().contains(worldPosition)) {
		if (!hoverScorelist) {
			setCursorType(nowWindow, sf::Cursor::Hand);
			menuHover.play();
		}
		hoverScorelist = true;
	}
	else {
		if (hoverScorelist) {
			setCursorType(nowWindow, sf::Cursor::Arrow);
		}
		hoverScorelist = false;
	}

	if (exit.getGlobalBounds().contains(worldPosition)) {
		if (!hoverExit) {
			menuHover.play();
			setCursorType(nowWindow, sf::Cursor::Hand);
		}
		hoverExit = true;
	}
	else {
		if (hoverExit) {
			setCursorType(nowWindow, sf::Cursor::Arrow);
		}
		hoverExit = false;
	}

IgnoreInteract:
	if (event.type == sf::Event::MouseButtonReleased) 
	{
		if ((worldPosition.y <= scoreListBG.getPosition().y)&&(scoreListAppear)) {
			closeScoreList();
			setCursorType(nowWindow, sf::Cursor::Arrow);
			hoverScorelist = false;
		}

		if (scoreListAppear) {
			return;
		}

		if (hoverPlay) {
			std::cout << "Play clicked" << std::endl;

			if (nowGame) {
				std::shared_ptr<UIBase> nextUI;
				std::shared_ptr<UIBase> loadUI;

				//Into load ui and send callback func into load ui
				nextUI = std::make_shared<GameMenu>(nowWindow, nowGame);
				nowGame->changeUI(nextUI);
				return;
			}
		}
		if (hoverScorelist) {
			std::cout << "Scorelist clicked" << std::endl;
			openScoreList();
		}
		if (hoverExit) {
			std::cout << "Exit clicked" << std::endl;
			nowWindow.close();
		}
	}
}

void StartMenu::openScoreList()
{
	scoreListAppear = true;
	std::thread t(&StartMenu::openScoreListAnim, this);
	t.detach();
}

void StartMenu::closeScoreList()
{
	std::thread t(&StartMenu::closeScoreListAnim, this);
	t.detach();
}

void StartMenu::openScoreListAnim()
{
	scoreListIsOpening = true;
	//Clock and time
	sf::Time duration = sf::seconds(4.f);
	sf::Time elapsedTime;
	sf::Clock clock;
	sf::Clock clockScoreHighestTitle;
	
	//init scoreListBG
	float a = scoreListBG.getPosition().x;
	float nowScoreListY = scoreListInitLoc.y;
	//init nowHighestScoreTitle
	float nowHighestScoreTitleY = scoreHighestTitleInitLoc.y;
	float b = scoreHighestTitleInitLoc.x;
	float highestScoreTitleInitTime = 0.3f;
	//init nowHighestScore
	float nowHighestScoreY = scoreHighestInitLoc.y;
	float c = scoreHighestInitLoc.x;
	float highestScoreInitTime = 0.4f;
	//init recentScoreTitle
	float nowrecentScoreTitleY = scoreRecentTitleInitLoc.y;
	float d = scoreRecentTitleInitLoc.x;
	float recentScoreTitleInitTime = 0.5f;
	//init recentScoreContent
	float nowrecentScoreY = scoreRecentInitLoc.y;
	float e = scoreRecentInitLoc.x;
	float recentScoreInitTime = 0.6f;

	while (elapsedTime < duration) {
		if (scoreListIsClosing)
			return;
		//Fade out loop
		float fadeRatio = elapsedTime.asSeconds() / (duration.asSeconds() - 3.2f);
		float volumeScoreListBG = fadeRatio;

		sf::Color color;

		if (volumeScoreListBG <= 1)
		{
			scoreListBG.setPosition(a, nowScoreListY - 50.f* volumeScoreListBG);
			scoreListBG.setColor(sf::Color(titleBG.getColor().r, titleBG.getColor().g, titleBG.getColor().b, 255 * volumeScoreListBG));
		}

		if (elapsedTime.asSeconds() > highestScoreTitleInitTime)
		{
			float fadeRatio1 = (elapsedTime.asSeconds() - highestScoreTitleInitTime)/(0.6f);
			float volume1 = fadeRatio1;

			if (volume1 >= 1)
				goto highestScoreTitleInitTimeEnd;

			scoreHighestTitle.setPosition(b, nowHighestScoreTitleY - 50.f * volume1);
			scoreHighestTitle.setFillColor(sf::Color(scoreHighestTitle.getFillColor().r, scoreHighestTitle.getFillColor().g, scoreHighestTitle.getFillColor().b, 255 * volume1));
			scoreHighestTitle.setOutlineColor(sf::Color(scoreHighestTitle.getOutlineColor().r, scoreHighestTitle.getOutlineColor().g, scoreHighestTitle.getOutlineColor().b, 255 * volume1));
		}
	highestScoreTitleInitTimeEnd:
		if (elapsedTime.asSeconds() > highestScoreInitTime)
		{
			float fadeRatio1 = (elapsedTime.asSeconds() - highestScoreInitTime) / (0.6f);
			float volume1 = fadeRatio1;

			if (volume1 >= 1)
				goto highestScoreInitTimeEnd;

			scoreHighest.setPosition(c, nowHighestScoreY - 50.f * volume1);
			scoreHighest.setFillColor(sf::Color(scoreHighest.getFillColor().r, scoreHighest.getFillColor().g, scoreHighest.getFillColor().b, 255 * volume1));
			scoreHighest.setOutlineColor(sf::Color(scoreHighest.getOutlineColor().r, scoreHighest.getOutlineColor().g, scoreHighest.getOutlineColor().b, 255 * volume1));
		}
	highestScoreInitTimeEnd:
		if (elapsedTime.asSeconds() > recentScoreTitleInitTime)
		{
			float fadeRatio1 = (elapsedTime.asSeconds() - recentScoreTitleInitTime) / (0.6f);
			float volume1 = fadeRatio1;

			if (volume1 >= 1)
				goto recentScoreTitleInitTimeEnd;

			scoreRecentTitle.setPosition(c, nowrecentScoreTitleY - 50.f * volume1);
			scoreRecentTitle.setFillColor(sf::Color(scoreRecentTitle.getFillColor().r, scoreRecentTitle.getFillColor().g, scoreRecentTitle.getFillColor().b, 255 * volume1));
			scoreRecentTitle.setOutlineColor(sf::Color(scoreRecentTitle.getOutlineColor().r, scoreRecentTitle.getOutlineColor().g, scoreRecentTitle.getOutlineColor().b, 255 * volume1));
		}
	recentScoreTitleInitTimeEnd:
		if (elapsedTime.asSeconds() > recentScoreInitTime)
		{
			float fadeRatio1 = (elapsedTime.asSeconds() - recentScoreInitTime) / (0.6f);
			float volume1 = fadeRatio1;

			if (volume1 >= 1)
				goto recentScoreInitTimeEnd;

			int count = 0;

			for (sf::Text* now : scoreRecent) 
			{
				(*now).setPosition(e, nowrecentScoreY - 50.f * volume1 + count * 40.f);
				(*now).setFillColor(sf::Color((*now).getFillColor().r, (*now).getFillColor().g, (*now).getFillColor().b, 255 * volume1));
				(*now).setOutlineColor(sf::Color((*now).getOutlineColor().r, (*now).getOutlineColor().g, (*now).getOutlineColor().b, 255 * volume1));
				count++;
			}
		}
	recentScoreInitTimeEnd:
		elapsedTime = clock.getElapsedTime();
	}
	scoreListIsOpening = false;
}

void StartMenu::closeScoreListAnim()
{
	//Score animation state
	scoreListIsClosing = true;
	//Clock and time
	sf::Time duration = sf::seconds(2.f);
	sf::Time elapsedTime;
	sf::Clock clock;
	sf::Clock clockScoreHighestTitle;

	//init scoreListBG
	float a = scoreListBG.getPosition().x;
	float nowScoreListY = scoreListTarLoc.y;
	//init nowHighestScoreTitle
	float nowHighestScoreTitleY = scoreHighestTitle.getPosition().y;
	float b = scoreHighestTitleInitLoc.x;
	float highestScoreTitleInitTime = 0.3f;
	//init nowHighestScore
	float nowHighestScoreY = scoreHighest.getPosition().y;
	float c = scoreHighestInitLoc.x;
	float highestScoreInitTime = 0.5f;
	//init recentScoreTitle
	float nowrecentScoreTitleY = scoreRecentTitle.getPosition().y;
	float d = scoreRecentTitleInitLoc.x;
	float recentScoreTitleInitTime = 0.6f;
	//init recentScoreContent
	auto first = scoreRecent.begin();
	sf::Text* ptr = *first;
	float nowrecentScoreY = ptr->getPosition().y;
	float e = scoreRecentInitLoc.x;
	float recentScoreInitTime = 0.7f;

	while (elapsedTime < duration) {
		//Fade out loop
		float fadeRatio = elapsedTime.asSeconds() / 0.8f;
		float volumeScoreListBG = 1 - fadeRatio;

		sf::Color color;

		if (fadeRatio <= 1)
		{
			scoreListBG.setPosition(a, nowScoreListY + 50.f * fadeRatio);
			scoreListBG.setColor(sf::Color(titleBG.getColor().r, titleBG.getColor().g, titleBG.getColor().b, 255 * volumeScoreListBG));
		}

		if (elapsedTime.asSeconds() > highestScoreTitleInitTime)
		{
			float fadeRatio1 = (elapsedTime.asSeconds() - highestScoreTitleInitTime) / 0.8f;
			float volume1 = 1 - fadeRatio1;

			if (fadeRatio1 >= 1)
				goto highestScoreTitleInitTimeEnd;

			scoreHighestTitle.setPosition(b, nowHighestScoreTitleY + 50.f * fadeRatio1);
			scoreHighestTitle.setFillColor(sf::Color(scoreHighestTitle.getFillColor().r, scoreHighestTitle.getFillColor().g, scoreHighestTitle.getFillColor().b, 255 * volume1));
			scoreHighestTitle.setOutlineColor(sf::Color(scoreHighestTitle.getOutlineColor().r, scoreHighestTitle.getOutlineColor().g, scoreHighestTitle.getOutlineColor().b, 255 * volume1));
		}
	highestScoreTitleInitTimeEnd:
		if (elapsedTime.asSeconds() > highestScoreInitTime)
		{
			float fadeRatio1 = (elapsedTime.asSeconds() - highestScoreInitTime) / 0.8f;
			float volume1 = 1 - fadeRatio1;

			if (fadeRatio1 >= 1)
				goto highestScoreInitTimeEnd;

			scoreHighest.setPosition(c, nowHighestScoreY + 50.f * fadeRatio1);
			scoreHighest.setFillColor(sf::Color(scoreHighest.getFillColor().r, scoreHighest.getFillColor().g, scoreHighest.getFillColor().b, 255 * volume1));
			scoreHighest.setOutlineColor(sf::Color(scoreHighest.getOutlineColor().r, scoreHighest.getOutlineColor().g, scoreHighest.getOutlineColor().b, 255 * volume1));
		}
	highestScoreInitTimeEnd:
		if (elapsedTime.asSeconds() > recentScoreTitleInitTime)
		{
			float fadeRatio1 = (elapsedTime.asSeconds() - recentScoreTitleInitTime) / 0.8f;
			float volume1 = 1 - fadeRatio1;

			if (fadeRatio1 >= 1)
				goto recentScoreTitleInitTimeEnd;

			scoreRecentTitle.setPosition(c, nowrecentScoreTitleY + 50.f * fadeRatio1);
			scoreRecentTitle.setFillColor(sf::Color(scoreRecentTitle.getFillColor().r, scoreRecentTitle.getFillColor().g, scoreRecentTitle.getFillColor().b, 255 * volume1));
			scoreRecentTitle.setOutlineColor(sf::Color(scoreRecentTitle.getOutlineColor().r, scoreRecentTitle.getOutlineColor().g, scoreRecentTitle.getOutlineColor().b, 255 * volume1));
		}
	recentScoreTitleInitTimeEnd:
		if (elapsedTime.asSeconds() > recentScoreInitTime)
		{
			float fadeRatio1 = (elapsedTime.asSeconds() - recentScoreInitTime) / (0.6f);
			float volume1 = 1 - fadeRatio1;

			if (fadeRatio1 >= 1)
				goto recentScoreInitTimeEnd;

			int count = 0;

			for (sf::Text* now : scoreRecent)
			{
				(*now).setPosition(e, nowrecentScoreY + 50.f * fadeRatio1 + count * 40.f);
				(*now).setFillColor(sf::Color((*now).getFillColor().r, (*now).getFillColor().g, (*now).getFillColor().b, 255 * volume1));
				(*now).setOutlineColor(sf::Color((*now).getOutlineColor().r, (*now).getOutlineColor().g, (*now).getOutlineColor().b, 255 * volume1));
				count++;
			}
		}
	recentScoreInitTimeEnd:
		elapsedTime = clock.getElapsedTime();
	}

	scoreListBG.setPosition(a, scoreListInitLoc.y);
	scoreListAppear = false;
	scoreListIsClosing = false;
}

void StartMenu::readScore() 
{
	scoreManager scoreMan(scoreHighest, scoreRecent);
}