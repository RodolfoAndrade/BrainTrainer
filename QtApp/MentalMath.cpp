#include "MentalMath.h"

MentalMath::MentalMath()
{
	// looking for mentalmath configuration saved in settings.json file
	control = Controller::getInstance("settings.json");
	digitsN1 = control->getMentalMathSettings("n1");
	digitsN2 = control->getMentalMathSettings("n2");

	generateEquation();
}

MentalMath::~MentalMath() {

}

void MentalMath::generateEquation()
{
	/* initialize random seed: */
	srand(time(NULL));

	if (digitsN1.compare("1") == 0) {
		/* generate numbers between 0 and 9: */
		n1 = rand() % 9;
	}
	else if (digitsN1.compare("2") == 0) {
		n1 = rand() % 99;
	}

	// generate digits for n2
	if (digitsN2.compare("1") == 0) {
		n2 = rand() % 9;
	}
	else if (digitsN2.compare("2") == 0) {
		n2 = rand() % 99;
	}
}

void MentalMath::setOperations(bool operations[4], int count)
{
	this->operations[0] = operations[0];
	this->operations[1] = operations[1];
	this->operations[2] = operations[2];
	this->operations[3] = operations[3];

	// randomly choosing a operation
	int opn = rand() % count + 1;
	if (this->operations[0] && opn) {
		opn--;
		operation = '+';
	}
	if (this->operations[1] && opn) {
		opn--;
		operation = '-';
	}
	if (this->operations[2] && opn) {
		opn--;
		operation = '*';
	}
	if (this->operations[3] && opn) {
		opn--;
		operation = '/';
	}
}

void MentalMath::setNumberDigits(std::string n1, std::string n2)
{
	this->digitsN1 = n1;
	this->digitsN2 = n2;
}

int MentalMath::getN1()
{
	return n1;
}

int MentalMath::getN2()
{
	return n2;
}

std::string MentalMath::getDigitsN1()
{
	return digitsN1;
}

std::string MentalMath::getDigitsN2()
{
	return digitsN2;
}

int MentalMath::getAnswer()
{
	switch (operation) {
		case '+' :
			return n1 + n2;
		case '-':
			return n1 - n2;
		case '*':
			return n1 * n2;
		case '/':
			return n1 / n2;
	}
}

char MentalMath::getOperation()
{
	return operation;
}
