#include "scoreManager.h"
#include <fstream>
#include <iostream>

scoreManager::scoreManager(sf::Text& highestScore, std::vector<sf::Text*>& recentScore)
{
	// 创建文件流对象
	filePath = "Content\\data\\score.txt";
	std::ifstream file(filePath);
	int currentLineNumber = 0;
	highestScoreText = &highestScore;
	recentScoreText = recentScore;

	if (recentScore.size() == 0) 
	{
		std::cout << "Warning, the score manager's recentScore vector is empty , please check start game ui" << std::endl;
	}
	// 检查文件是否成功打开
	if (file.is_open()) {
		// 文件成功打开，可以读取文件内容
		std::string content;
		while (std::getline(file, content)) {
			currentLineNumber++;
			ScoreCont.push_back(content);
			if (currentLineNumber == 1) {
				highestScoreCont = content;
				highestScore.setString(highestScoreCont); // 读取score数据
				continue;
			}

			if (recentScore[currentLineNumber - 2] == nullptr)
				continue;

			recentScore[currentLineNumber - 2]->setString(content);
		}
		file.close(); // 关闭文件流
	}
	else {
		// 文件打开失败
		std::cerr << "Failed to open file: " << std::endl;
	}
}

scoreManager::scoreManager()
{
	readData();
}

void scoreManager::readData()
{
	// 创建文件流对象
	filePath = "Content\\data\\score.txt";
	std::ifstream file(filePath);
	int currentLineNumber = 0;

	// 检查文件是否成功打开
	if (file.is_open()) {
		// 文件成功打开，可以读取文件内容
		std::string content;
		while (std::getline(file, content)) {
			ScoreCont.push_back(content);
			currentLineNumber++;
			if (currentLineNumber == 1) {
				highestScoreCont = content; // 读取score数据
				continue;
			}
		}
		file.close(); // 关闭文件流
	}
	else {
		// 文件打开失败
		std::cerr << "Failed to open file: " << std::endl;
	}
}

bool scoreManager::freshText(sf::Text& highestScore, std::vector<sf::Text*>& recentScore)
{
	// 创建文件流对象
	filePath = "Content\\data\\score.txt";
	std::ifstream file(filePath);
	int currentLineNumber = 0;
	highestScoreText = &highestScore;
	recentScoreText = recentScore;

	if (recentScore.size() == 0)
	{
		std::cout << "Warning, the score manager's recentScore vector is empty , please check start game ui" << std::endl;
		return false;
	}
	// 检查文件是否成功打开
	if (file.is_open()) {
		// 文件成功打开，可以读取文件内容
		std::string content;
		while (std::getline(file, content)) {
			currentLineNumber++;
			if (currentLineNumber == 1) {
				highestScoreCont = content;
				highestScore.setString(highestScoreCont); // 读取score数据
				continue;
			}

			if (recentScore[currentLineNumber - 2] == nullptr)
				continue;

			recentScore[currentLineNumber - 2]->setString(content);
		}
		file.close(); // 关闭文件流
	}
	else {
		// 文件打开失败
		std::cerr << "Failed to open file: " << std::endl;
		return false;
	}
	return true;
}

bool scoreManager::freshText(sf::Text& highestScore)
{
	highestScore.setString(highestScoreCont);
	sf::FloatRect textBounds = highestScore.getLocalBounds();
	highestScore.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	return true;
}

std::string scoreManager::getHighestScore()
{
	return highestScoreCont;
}

void scoreManager::setHighestScore(std::string cont)
{
	highestScoreCont = cont;  

	std::ifstream infile(filePath);
	std::vector<std::string> lines;
	std::string line;

	// 读取文件内容到向量中
	while (std::getline(infile, line)) {
		lines.push_back(line);
	}

	infile.close();

	// 检查行号是否有效
	if (1 > 0 && 1 <= lines.size()) {
		// 修改指定行的数据
		lines[0] = cont; // 行号从1开始，向量索引从0开始
	}
	else {
		std::cerr << "Invalid line number" << std::endl;
		return;
	}

	// 将修改后的内容写回文件
	std::ofstream outfile(filePath);

	for (const auto& l : lines) 
	{
		outfile << l << std::endl;
	}
}

std::vector<std::string> scoreManager::getAllScoreCont()
{
	return ScoreCont;
}

void scoreManager::removeThenAddRecent(std::string cont)
{
	//Refresh the highest value
	int nowCont;
	try {
		nowCont = std::stoi(cont);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid argument: " << e.what() << std::endl;
		nowCont = 0;
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Out of range: " << e.what() << std::endl;
		nowCont = 0;
	}

	int nowHighestCont;
	try {
		nowHighestCont = std::stoi(highestScoreCont);

	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid argument: " << e.what() << std::endl;
		nowHighestCont = 0;
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Out of range: " << e.what() << std::endl;
		nowHighestCont = 0;
	}

	if (nowCont > nowHighestCont) 
	{
		highestScoreCont = cont;
	}

	std::ifstream infile(filePath);
	std::vector<std::string> linesPrev;
	std::vector<std::string> linesTar;
	std::string line;

	// 读取文件内容到向量中
	while (std::getline(infile, line)) {
		linesPrev.push_back(line);
	}
	linesTar = linesPrev;
	
	infile.close();

	linesTar[1] = cont;
	linesTar[2] = linesPrev[1];
	linesTar[3] = linesPrev[2];

	ScoreCont = linesTar;
	// 将修改后的内容写回文件
	std::ofstream outfile(filePath);

	for (const auto& l : linesTar) {
		outfile << l << std::endl;
	}
}
