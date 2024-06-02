#include "scoreManager.h"
#include <fstream>
#include <iostream>

scoreManager::scoreManager(sf::Text& highestScore, std::vector<sf::Text*>& recentScore)
{
	// �����ļ�������
	filePath = "Content\\data\\score.txt";
	std::ifstream file(filePath);
	int currentLineNumber = 0;
	highestScoreText = &highestScore;
	recentScoreText = recentScore;

	if (recentScore.size() == 0) 
	{
		std::cout << "Warning, the score manager's recentScore vector is empty , please check start game ui" << std::endl;
	}
	// ����ļ��Ƿ�ɹ���
	if (file.is_open()) {
		// �ļ��ɹ��򿪣����Զ�ȡ�ļ�����
		std::string content;
		while (std::getline(file, content)) {
			currentLineNumber++;
			ScoreCont.push_back(content);
			if (currentLineNumber == 1) {
				highestScoreCont = content;
				highestScore.setString(highestScoreCont); // ��ȡscore����
				continue;
			}

			if (recentScore[currentLineNumber - 2] == nullptr)
				continue;

			recentScore[currentLineNumber - 2]->setString(content);
		}
		file.close(); // �ر��ļ���
	}
	else {
		// �ļ���ʧ��
		std::cerr << "Failed to open file: " << std::endl;
	}
}

scoreManager::scoreManager()
{
	readData();
}

void scoreManager::readData()
{
	// �����ļ�������
	filePath = "Content\\data\\score.txt";
	std::ifstream file(filePath);
	int currentLineNumber = 0;

	// ����ļ��Ƿ�ɹ���
	if (file.is_open()) {
		// �ļ��ɹ��򿪣����Զ�ȡ�ļ�����
		std::string content;
		while (std::getline(file, content)) {
			ScoreCont.push_back(content);
			currentLineNumber++;
			if (currentLineNumber == 1) {
				highestScoreCont = content; // ��ȡscore����
				continue;
			}
		}
		file.close(); // �ر��ļ���
	}
	else {
		// �ļ���ʧ��
		std::cerr << "Failed to open file: " << std::endl;
	}
}

bool scoreManager::freshText(sf::Text& highestScore, std::vector<sf::Text*>& recentScore)
{
	// �����ļ�������
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
	// ����ļ��Ƿ�ɹ���
	if (file.is_open()) {
		// �ļ��ɹ��򿪣����Զ�ȡ�ļ�����
		std::string content;
		while (std::getline(file, content)) {
			currentLineNumber++;
			if (currentLineNumber == 1) {
				highestScoreCont = content;
				highestScore.setString(highestScoreCont); // ��ȡscore����
				continue;
			}

			if (recentScore[currentLineNumber - 2] == nullptr)
				continue;

			recentScore[currentLineNumber - 2]->setString(content);
		}
		file.close(); // �ر��ļ���
	}
	else {
		// �ļ���ʧ��
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

	// ��ȡ�ļ����ݵ�������
	while (std::getline(infile, line)) {
		lines.push_back(line);
	}

	infile.close();

	// ����к��Ƿ���Ч
	if (1 > 0 && 1 <= lines.size()) {
		// �޸�ָ���е�����
		lines[0] = cont; // �кŴ�1��ʼ������������0��ʼ
	}
	else {
		std::cerr << "Invalid line number" << std::endl;
		return;
	}

	// ���޸ĺ������д���ļ�
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

	// ��ȡ�ļ����ݵ�������
	while (std::getline(infile, line)) {
		linesPrev.push_back(line);
	}
	linesTar = linesPrev;
	
	infile.close();

	linesTar[1] = cont;
	linesTar[2] = linesPrev[1];
	linesTar[3] = linesPrev[2];

	ScoreCont = linesTar;
	// ���޸ĺ������д���ļ�
	std::ofstream outfile(filePath);

	for (const auto& l : linesTar) {
		outfile << l << std::endl;
	}
}
