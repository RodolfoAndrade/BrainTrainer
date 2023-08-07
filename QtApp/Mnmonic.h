#pragma once

#include <QObject>
#include <QDebug>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string> 

class Mnmonic  : public QObject
{
	Q_OBJECT

public:
	int numberDigits = 3;
	QString digits;

	explicit Mnmonic(QObject *parent = 0);
	~Mnmonic();
	Q_INVOKABLE void print(QString txt);
	Q_INVOKABLE void setNumberDigits(int value);
	Q_INVOKABLE QString generateDigits();
	Q_INVOKABLE bool checkDigits(QString digits1);
};
