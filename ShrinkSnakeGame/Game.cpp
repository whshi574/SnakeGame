#include "Game.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "StartMenu.h"
#include <chrono>
#include <thread>
#include <iostream>

Game::Game()
{
	mainWindow = new sf::RenderWindow(sf::VideoMode(1000, 800), name);
    currentUI = std::make_shared<StartMenu>(*mainWindow, this);
    windowInitSize = mainWindow->getSize();
    currentUI->init();
}

Game::~Game()
{

}

void Game::Render()
{
    mainWindow->clear();
    currentUI->render(*mainWindow);
    mainWindow->display();
}

void Game::Update()
{
    currentUI->update();
    mainWindow->setSize(windowInitSize);
}

void Game::HandleInput()
{
    sf::Event event;
    
    while (mainWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mainWindow->close();

        currentUI->handleInput(*mainWindow, event);
    }
}

void Game::runLoop()
{

    auto previousTime = std::chrono::high_resolution_clock::now();

    while (mainWindow->isOpen())
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime).count();

        if (elapsedTime >= frameTime)
        {
            //One Frame loop
            //One update frame
            Update();
            //One handleinput frame
            HandleInput();
            //One render frame
            Render();
            previousTime = currentTime;
        }
    }
}

sf::RenderWindow* Game::GetWindow()
{
    return mainWindow;
}

void Game::changeUI(std::shared_ptr<UIBase> next)
{
    //currentUI.reset();
    if (!next) {
        std::cout << "NextUI is nullptr" << std::endl;
        return;
    }
    currentUI = next;
}
