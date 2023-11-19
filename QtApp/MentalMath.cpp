#include "MentalMath.h"

MentalMath::MentalMath()
{
	qDebug() << "MentalMath constructor";

	// looking for mentalmath configuration saved in settings.json file
	control = Controller::getInstance();
	numberDigits = control->getMentalMathSettings();

	generateEquation();
}

void MentalMath::generateEquation()
{
	int n = 9;

	//if full digits
	if (numberDigits.compare("1") == 0 || numberDigits.compare("2") == 0) {
		if (numberDigits.compare("1") == 0) n = 9;
		else if (numberDigits.compare("2") == 0) n = 99;

		/* initialize random seed: */
		srand(time(NULL));
		/* generate numbers between 0 and 9: */
		n1 = rand() % n;
		n2 = rand() % n;
	}
	else {
		if (numberDigits.compare("1.2") == 0) {
			n1 = rand() % 9;
			n2 = rand() % 99;
		}
	}
}

std::string MentalMath::getNumberDigits()
{
	return numberDigits;
}

void MentalMath::setNumberDigits(std::string numberDigits)
{
	this->numberDigits = numberDigits;
}

int MentalMath::getN1()
{
	return n1;
}

int MentalMath::getN2()
{
	return n2;
}

int MentalMath::getAnswer()
{
	return n1 * n2;
}
