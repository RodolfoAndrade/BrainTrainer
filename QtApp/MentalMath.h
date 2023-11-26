#pragma once
#include "Controller.h"

class MentalMath
{
private:
	std::string digitsN1;
	std::string digitsN2;
	int n1;
	int n2;
	Controller* control;
public:
	MentalMath();
	void setNumberDigits(std::string n1, std::string n2);
	void generateEquation();
	int getN1();
	int getN2();
	std::string getDigitsN1();
	std::string getDigitsN2();
	int getAnswer();
};

