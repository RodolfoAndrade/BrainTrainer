#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class MentalMath
{
private:
	std::string numberDigits;
	int n1;
	int n2;
	std::vector<std::vector<int>> score;
public:
	MentalMath();
	std::string getNumberDigits();
	void setNumberDigits(std::string numberDigits);
	void generateEquation();
	int getN1();
	int getN2();
	int getAnswer();
	void loadProgress();
	void incrementScore();
	void saveProgress();
	void clearScore();
};

