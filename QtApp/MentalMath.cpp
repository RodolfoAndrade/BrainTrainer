#include "MentalMath.h"

MentalMath::MentalMath(QObject *parent)
	: QObject(parent)
{
	readProgress();
}

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
	MentalMath::equation = equation;

	return equation;
}

bool MentalMath::checkAnswer(QString answer)
{
	int ans = n1 * n2;
	bool flag;
	if (QString::compare(answer, "", Qt::CaseInsensitive) == 0) {
		return false;
	}
	else {
		qDebug() << "Message from QML: " << answer.toInt() << ans;
		flag = answer.toInt() == ans;
		if (flag) {
			saveProgress(equation);
		}
		return flag;
	}
}

void MentalMath::saveProgress(QString equation)
{
	ofstream newFile("math_progress.txt");
	if (in.find(equation) == in.end()) {
		in[equation] = 1;
	}
	else {
		in[equation]++;
	}

	// Get an iterator pointing to the first element in the map
	map<QString, int>::iterator it = in.begin();

	// Iterate through the map and print the elements
	while (newFile.is_open() && it != in.end())
	{
		newFile << it->first.toStdString() << ":" << it->second << endl;
		++it;
	}
	newFile.close();
}

void MentalMath::readProgress()
{
	ifstream newFile("math_progress.txt");
	string line, key, val;
	if (newFile.is_open())
	{
		while (getline(newFile, line))
		{
			qDebug() << line << '\n';
			key = line.substr(0, line.find(":"));
			val = line.substr(line.find(":") + 1, line.size());
			qDebug() << key << ":" << val << '\n';
			in[QString::fromStdString(key)] = stoi(val);
		}
		newFile.close();
	}
}
