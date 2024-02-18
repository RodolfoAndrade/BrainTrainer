#pragma once
#include <string>
#include <time.h>

class Mnmonic
{
private:
	int digitsLength;
	std::string digits;
public:
	Mnmonic();
	int getDigitsLength();
	void generateDigits(int numberDigits);
	std::string getDigits();
};

