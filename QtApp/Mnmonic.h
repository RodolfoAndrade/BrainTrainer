#pragma once
#include "Controller.h"

class Mnmonic
{
private:
	Controller* control;
	int digitsLength;
	std::string digits;
public:
	Mnmonic();
	int getDigitsLength();
	void generateDigits(int numberDigits);
	std::string getDigits();
};

