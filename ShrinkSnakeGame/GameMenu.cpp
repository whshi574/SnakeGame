#include "GameMenu.h"
#include <iostream>
#include <thread>
#include <SFML/Window.hpp>
#include "Game.h"
#include "ResourceManager.h"
#include "StartMenu.h"
#include "scoreManager.h"

GameMenu::GameMenu(sf::RenderWindow& nowWindow, Game* game)
{
	//Get game address
	nowGame = game;

	//Get now window information
	sf::Vector2u windowSize = nowWindow.getSize();
	setCursorType(nowWindow, sf::Cursor::Arrow);

	//Start menu UI text init
	text.loadFromFile("Content\\font\\StartMenuButton.ttf");

	//Set Game UI text info
	score.setFont(text);
	score.setFillColor(sf::Color::White);
	score.setString("Your Score:");
	score.setCharacterSize(35);
	sf::FloatRect textBounds = score.getLocalBounds();
 	score.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	AlignedCenterText(score);
	score.setPosition(200.f, 40.f);

	scoreContent.setFont(text);
	scoreContent.setFillColor(sf::Color::White);
	scoreContent.setString("0");
	scoreContent.setCharacterSize(35);
	AlignedCenterText(scoreContent);
	scoreContent.setPosition(score.getGlobalBounds().left + score.getGlobalBounds().width + 20.f, 40.f);

	gameOverScore.setFont(text);
	gameOverScore.setFillColor(sf::Color(0x7ED957ff));
	gameOverScore.setOutlineColor(sf::Color::White);
	gameOverScore.setOutlineThickness(2.f);
	gameOverScore.setCharacterSize(70);
	AlignedCenterText(gameOverScore);
	gameOverScore.setPosition(windowSize.x / 2, windowSize.y / 2 - 120.f);

	gameOverTitle.setFont(text);
	gameOverTitle.setFillColor(sf::Color::White);
	gameOverTitle.setOutlineColor(sf::Color(0x5E17EBff));
	gameOverTitle.setOutlineThickness(2.f);
	gameOverTitle.setString("GAME OVER");
	gameOverTitle.setCharacterSize(75);
	AlignedCenterText(gameOverTitle);
	gameOverTitle.setPosition(windowSize.x / 2, windowSize.y / 2 - 40.f);

	scoreManager scoreMan;

	highestScoreTitle.setFont(text);
	highestScoreTitle.setFillColor(sf::Color(0x5E17EBff));
	highestScoreTitle.setOutlineColor(sf::Color(0x7ED957ff));
	highestScoreTitle.setOutlineThickness(2.f);
	highestScoreTitle.setString("The highest score");
	highestScoreTitle.setCharacterSize(30);
	AlignedCenterText(highestScoreTitle);
	highestScoreTitle.setPosition(windowSize.x / 2, windowSize.y / 2 + 50.f);

	highestScoreCont.setFont(text);
	highestScoreCont.setFillColor(sf::Color::White);
	highestScoreCont.setOutlineColor(sf::Color(0x5E17EBff));
	highestScoreCont.setString(scoreMan.getHighestScore());
	highestScoreCont.setCharacterSize(26);
	AlignedCenterText(highestScoreCont);
	highestScoreCont.setPosition(windowSize.x / 2, windowSize.y / 2 + 90.f);

	//Set Game Icon info
	loadAndSetSprite(spriteStop, texStop,"Content\\images\\Stop.png");
	spriteStop.setPosition(windowSize.x - 50.f, 40.f);

	loadAndSetSprite(spriteSandClock, texSandClock, "Content\\images\\ShaLouIcon.png");
	spriteSandClock.setPosition(windowSize.x - 130.f, 40.f);

	loadAndSetSprite(spriteSmallPanelBG, texSmallPanelBG, "Content\\images\\smallPanelBG.png");
	spriteSmallPanelBG.setPosition(windowSize.x/2, windowSize.y / 2);

	loadAndSetSprite(spriteGamePauseBG, texGamePauseBG, "Content\\images\\GamePauseBG.png");
	spriteGamePauseBG.setPosition(windowSize.x / 2, windowSize.y / 2);

	loadAndSetSprite(spriteContinueIcon, texContinueIcon, "Content\\images\\ContinueIcon.png");
	spriteContinueIcon.setPosition(windowSize.x / 2 - 100.f, windowSize.y / 2);
	spriteContinueIcon.setScale(0.2,0.2);

	loadAndSetSprite(spriteRestartIcon, texRestartIcon, "Content\\images\\Restart.png");
	spriteRestartIcon.setPosition(windowSize.x / 2, windowSize.y / 2);

	loadAndSetSprite(spriteHomeIcon, texHomeIcon, "Content\\images\\BackToMenu.png");
	spriteHomeIcon.setPosition(windowSize.x / 2 + 100.f, windowSize.y / 2);

	//Set music info
	buttonHover.setVolume(100.0f);
	buttonHover.openFromFile("Content\\music\\menu-screen-mouse-over.wav");

	//Todo: maybe need delete
	envir = new Map(nowWindow);

	//Set snake info
	player = std::make_unique<Snake>(nowWindow);
	player->init(envir);
	player->setUpUItoSnake(this);

	//Warning pointer
	Snake* snakePtr = player.get();
	envir->setPlayer(snakePtr);

	// 启动一个新线程来执行延迟函数
	std::thread t(&GameMenu::beginPlayGameLoopMusic, this);
	t.detach();
}

GameMenu::~GameMenu()
{
	UIBase::~UIBase();
	sf::Time duration = sf::seconds(1.0f);
	sf::Time elapsedTime;
	sf::Clock clock;

	if (nowGame == nullptr) {
		std::cout << "Warning, Gamemenu destructor have not now Game pointer" << std::endl;
	}

	sf::RenderWindow* nowWindow = nowGame->GetWindow();

	sf::RectangleShape rectangle(sf::Vector2f(1000, 800)); // 大小为1000x800

	while (elapsedTime < duration) {
		//Fade out loop
		float fadeRatio = elapsedTime / duration;
		float volume = 1.0f - fadeRatio;
		std::cout << "fadeRatio: " << fadeRatio << std::endl;

		rectangle.setFillColor(sf::Color(0,0,0,255* fadeRatio));
		gameLoop.setVolume(gameLoop .getVolume() * volume);

		nowWindow->clear();
		render(*nowWindow);
		nowWindow->draw(rectangle);
		nowWindow->display();

		elapsedTime = clock.getElapsedTime();
	}

	delete envir;
}

void GameMenu::init()
{
}

void GameMenu::update()
{
	player->update();
}

void GameMenu::render(sf::RenderWindow& nowWindow)
{
	envir->render(nowWindow);
	envir->getItemManager().renderAll(nowWindow);
	player->render(nowWindow);
	nowWindow.draw(score);
	nowWindow.draw(spriteStop);
	nowWindow.draw(spriteSandClock);
	nowWindow.draw(scoreContent);

	if (isGamePause) 
	{
		nowWindow.draw(spriteGamePauseBG);
		nowWindow.draw(spriteContinueIcon);
		nowWindow.draw(spriteRestartIcon);
		nowWindow.draw(spriteHomeIcon);

	}

	if (canShowGameOver)
	{
		nowWindow.draw(spriteSmallPanelBG);
		nowWindow.draw(spriteRestartIcon);
		nowWindow.draw(highestScoreTitle);
		nowWindow.draw(highestScoreCont);
		nowWindow.draw(spriteHomeIcon);
		nowWindow.draw(gameOverTitle);
		nowWindow.draw(gameOverScore);
	}
}

void GameMenu::handleInput(sf::RenderWindow& nowWindow, sf::Event event)
{
	player->handleInput(nowWindow, event);

	sf::Vector2i mousePosition = sf::Mouse::getPosition(nowWindow);
	sf::Vector2f worldPosition = nowWindow.mapPixelToCoords(mousePosition);

	if (isGameOver)
		goto hoverStopClickEnd;

	if (spriteStop.getGlobalBounds().contains(worldPosition)) 
	{
		std::cout << "Stop hover" << std::endl;
		if (!hoverStop) {
			buttonHover.play();
			spriteStop.setColor(sf::Color::Black);
			setCursorType(nowWindow, sf::Cursor::Hand);
		}
		hoverStop = 1;
	}
	else {
		if (hoverStop) 
		{
			spriteStop.setColor(sf::Color::White);
			setCursorType(nowWindow, sf::Cursor::Arrow);
		}

		hoverStop = 0;
	}
hoverStopInteractEnd:
	if (hoverStop) 
	{
		if (event.type == sf::Event::MouseButtonReleased) 
		{
			std::cout << "Stop button hover clicked" << std::endl;
			if (isGamePause) 
			{
				//now game pause to none game pause
				PauseToGaming();
			}
			else {
				//now none game pause to game pause
				GamingToPause();
			}
		}
	}
hoverStopClickEnd:
	if (!isGamePause || isGameOver)
		goto GamePauseInputEnd;

	if (spriteContinueIcon.getGlobalBounds().contains(worldPosition))
	{
		std::cout << "spriteContinueIcon hover" << std::endl;
		if (!hoverContinue) {
			buttonHover.play();
			spriteContinueIcon.setColor(sf::Color::Black);
			setCursorType(nowWindow, sf::Cursor::Hand);
		}
		hoverContinue = 1;
	}
	else {
		if (hoverContinue)
		{
			spriteContinueIcon.setColor(sf::Color::White);
			setCursorType(nowWindow, sf::Cursor::Arrow);
		}

		hoverContinue = 0;
	}
	if (hoverContinue)
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			std::cout << "hoverContinue button hover clicked" << std::endl;
			PauseToGaming();
		}
	}

GamePauseInputEnd:

	if (!isGamePause && !canShowGameOver)
		goto GamePauseContinueEnd;

	if (spriteHomeIcon.getGlobalBounds().contains(worldPosition))
	{
		std::cout << "spriteHomeIcon hover" << std::endl;
		if (!hoverHome) {
			buttonHover.play();
			spriteHomeIcon.setColor(sf::Color::Black);
			setCursorType(nowWindow, sf::Cursor::Hand);
		}
		hoverHome = 1;
	}
	else {
		if (hoverHome)
		{
			spriteHomeIcon.setColor(sf::Color::White);
			setCursorType(nowWindow, sf::Cursor::Arrow);
		}

		hoverHome = 0;
	}
	if (hoverHome)
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			std::cout << "hoverHome button hover clicked" << std::endl;

			std::shared_ptr<UIBase> nextUI;
			nextUI = std::make_shared<StartMenu>(nowWindow, nowGame);
			nowGame->changeUI(nextUI);
			nextUI->init();
		}
	}

	if (spriteRestartIcon.getGlobalBounds().contains(worldPosition))
	{
		std::cout << "spriteRestartIcon hover" << std::endl;
		if (!hoverRestart) {
			buttonHover.play();
			spriteRestartIcon.setColor(sf::Color::Black);
			setCursorType(nowWindow, sf::Cursor::Hand);
		}
		hoverRestart = 1;
	}
	else {
		if (hoverRestart)
		{
			spriteRestartIcon.setColor(sf::Color::White);
			setCursorType(nowWindow, sf::Cursor::Arrow);
		}

		hoverRestart = 0;
	}
	if (hoverRestart)
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			std::cout << "hoverRestart button hover clicked" << std::endl;

			std::shared_ptr<UIBase> nextUI;
			nextUI = std::make_shared<GameMenu>(nowWindow, nowGame);
			nowGame->changeUI(nextUI);
			nextUI->init();
		}
	}
GamePauseContinueEnd:
	return;
}

void GameMenu::addScore(int delta)
{
	nowScore += delta;
	freshScore();
}

void GameMenu::freshScore()
{
	scoreContent.setString(std::to_string(nowScore));
}

void GameMenu::GamingToPause()
{
	player->changeGamePause(true);
	openPauseUI();
	isGamePause = true;
}

void GameMenu::PauseToGaming()
{
	player->changeGamePause(false);
	closePauseUI();
	isGamePause = false;
}

void GameMenu::openPauseUI()
{
	std::thread t(&GameMenu::openPauseUIAnim, this);
	t.detach();
}

void GameMenu::closePauseUI()
{
	std::thread t(&GameMenu::closePauseUIAnim, this);
	t.detach();
}

void GameMenu::openPauseUIAnim()
{
	std::cout << "Open pause animation" << std::endl;
}

void GameMenu::closePauseUIAnim()
{
	std::cout << "Close pause animation" << std::endl;
}

void GameMenu::setIsGameOver(bool isGameOverVar)
{
	isGameOver = isGameOverVar;
}

void GameMenu::openGGUI()
{
	setIsGameOver(true);

	spriteRestartIcon.setPosition(720.f, 200.f);
	spriteHomeIcon.setPosition(280.f, 200.f);

	//Todo: 多线程访问同一数据出现了问题
	gameOverScore.setString(scoreContent.getString());
	AlignedCenterText(gameOverScore);

	scoreManager temp;

	temp.removeThenAddRecent(scoreContent.getString());
	temp.freshText(highestScoreCont);

	std::thread t(&GameMenu::openGGUIAnim, this);
	t.detach();
}

void GameMenu::openGGUIAnim()
{
	//Todo: 线程安全检查
	canShowGameOver = true;
	std::cout << "Open GameOver animation" << std::endl;
}

void GameMenu::bindInteractButton(sf::Sprite& nowSprite, bool& isHover, void(*hover)(sf::Sprite&), void(*unHover)(sf::Sprite&))
{
	if (!isHover) 
	{
		hover(nowSprite);
	}
	else 
	{
		unHover(nowSprite);
	}
}

/*void GameMenu::changeState(GameState nextState)
{
	GameState lastState = nowState;

	switch (nextState.getState())
	{
	case Gaming:
		break;
	case GamePause:
		break;
	case GameOver:
		break;
	default:
		break;
	}
}*/

void GameMenu::beginPlayGameLoopMusic()
{
	// 等待 2 秒钟
	std::this_thread::sleep_for(std::chrono::seconds(1));

	gameLoop.openFromFile("Content\\music\\GameLoop.mp3");
	gameLoop.setLoop(true);
	gameLoop.setVolume(0);
	gameLoop.play();

	// 声音线性增加的总时间（秒）
	float totalTime = 3.f;

	// 每次增加声音的时间间隔（毫秒）
	int interval = 50;

	// 声音增加的步长
	float step = 1.0f / (totalTime * 1000 / interval);

	// 声音音量
	float volume = 0.0f;

	// 每次增加声音并等待一段时间
	while (volume < 1.0f) {
		volume += step;
		if (volume > 1.0f) {
			volume = 1.0f; // 确保音量不超过 1
		}
		gameLoop.setVolume(10 * volume); // 设置音量（范围 0-100）

		// 等待一段时间
		std::this_thread::sleep_for(std::chrono::milliseconds(interval));
	}
}
