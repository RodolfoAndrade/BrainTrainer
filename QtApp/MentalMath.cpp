#include "MentalMath.h"

MentalMath::MentalMath(QObject *parent)
	: QObject(parent)
{}

MentalMath::~MentalMath()
{}

QString MentalMath::generateEquation()
{
	QString equation;

	/* initialize random seed: */
	srand(time(NULL));
	/* generate numbers between 0 and 9: */
	n1 = rand() % 9;
	n2 = rand() % 9;

	equation += QString::number(n1);
	equation += "x";
	equation += QString::number(n2);

	return equation;
}

bool MentalMath::checkAnswer(QString answer)
{
	int ans = n1 * n2;
	if (QString::compare(answer, "", Qt::CaseInsensitive) == 0) {
		return false;
	}
	else {
		qDebug() << "Message from QML: " << answer.toInt() << ans;
		return answer.toInt() == ans;
	}
}
