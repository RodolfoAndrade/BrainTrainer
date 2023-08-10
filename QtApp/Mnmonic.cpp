#include "Mnmonic.h"

Mnmonic::Mnmonic(QObject *parent)
	: QObject(parent)
{
	readProgress();
}

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
		if (i != 0 && i % 2 == 0) digits += "-";
		digits += QString::number(n);
	}

	Mnmonic::digits = digits;
	return digits;
}

bool Mnmonic::checkDigits(QString digits1)
{
	print(digits1);
	print(Mnmonic::digits);
	bool flag = QString::compare(Mnmonic::digits, digits1, Qt::CaseInsensitive) == 0;
	if (flag) {
		saveProgress(digits1);
	}
	return flag;
}

QString Mnmonic::getDigits()
{
	return digits;
}

void Mnmonic::saveProgress(QString digits1)
{
	ofstream newFile("progress.txt");
	QStringList list = digits1.split("-");
	for (size_t i = 0; i < list.count(); i++)
	{
		//qDebug() << list[i];
		if (in.find(list[i]) == in.end()) {
			in[list[i]] = 1;
		}
		else {
			in[list[i]]++;
		}
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

void Mnmonic::readProgress()
{
	ifstream newFile("progress.txt");
	string line, key, val;
	if (newFile.is_open())
	{
		while (getline(newFile, line))
		{
			qDebug() << line << '\n';
			key = line.substr(0, line.find(":"));
			val = line.substr(line.find(":")+1, line.size());
			qDebug() << key << ":" << val << '\n';
			in[QString::fromStdString(key)] = stoi(val);
		}
		newFile.close();
	}
}
