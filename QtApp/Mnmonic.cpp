#include "Mnmonic.h"

Mnmonic::Mnmonic(QObject *parent)
	: QObject(parent)
{}

Mnmonic::~Mnmonic()
{}

void Mnmonic::print(QString txt)
{
	qDebug() << "Message from QML: " << txt;
}

void Mnmonic::setNumberDigits(int value)
{
	numberDigits = value;
}

QString Mnmonic::generateDigits()
{
	QString digits;
	int n;

	/* initialize random seed: */
	srand(time(NULL));

	for (size_t i = 0; i < numberDigits; i++)
	{
		/* generate secret number between 0 and 9: */
		n = rand() % 9;
		digits += QString::number(n);
	}

	Mnmonic::digits = digits;
	return digits;
}

bool Mnmonic::checkDigits(QString digits1)
{
	print(digits1);
	print(Mnmonic::digits);
	return QString::compare(Mnmonic::digits, digits1, Qt::CaseInsensitive) == 0;
}

QString Mnmonic::getDigits()
{
	return digits;
}
