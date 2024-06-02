#pragma once
#include <string>
#include <SFML/Graphics/Text.hpp>

class scoreManager
{

	std::string filePath;
	std::string highestScoreCont;
	//All score data, include highest and recent
	std::vector<std::string> ScoreCont;
	sf::Text* highestScoreText;
	std::vector<sf::Text*> recentScoreText;

public:
	//for read constructor
	scoreManager(sf::Text& highestScore, std::vector<sf::Text*>& recentScore);
	//common constructor
	scoreManager();

	void readData();
	bool freshText(sf::Text& highestScore, std::vector<sf::Text*>& recentScore);
	bool freshText(sf::Text& highestScore);

	std::string getHighestScore();
	void setHighestScore(std::string cont);

	std::vector<std::string> getAllScoreCont();
	void removeThenAddRecent(std:: string cont);
};