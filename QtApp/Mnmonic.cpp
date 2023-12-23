#include "Mnmonic.h"

Mnmonic::Mnmonic()
{
	// looking for mentalmath configuration saved in settings.json file
	control = Controller::getInstance("settings.json");
	digitsLength = std::stoi(control->getMnmonicSettings());
}

int Mnmonic::getDigitsLength()
{
	return digitsLength;
}

void Mnmonic::generateDigits(int numberDigits)
{
	digits = "";
	int n;

	/* initialize random seed: */
	srand(time(NULL));

	for (size_t i = 0; i < numberDigits; i++)
	{
		/* generate secret number between 0 and 9: */
		n = rand() % 9;
		if (i != 0 && i % 2 == 0) digits += "-";
		digits += std::to_string(n);
	}
}

std::string Mnmonic::getDigits()
{
	return digits;
}
