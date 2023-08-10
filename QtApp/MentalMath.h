#pragma once

#include <QObject>
#include <QDebug>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string> 

class MentalMath  : public QObject
{
	Q_OBJECT

public:
	int n1 = 0;
	int n2 = 0;
	QString op;

	explicit MentalMath(QObject *parent = 0);
	~MentalMath();
	Q_INVOKABLE QString generateEquation();
	Q_INVOKABLE bool checkAnswer(QString answer);
};