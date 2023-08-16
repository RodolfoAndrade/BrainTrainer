#include "MentalMathGame.h"

MentalMathGame::MentalMathGame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.checkButton, SIGNAL(clicked()), this, SLOT(checkAnswer()));

	generateEquation();
	loadProgress();
}

MentalMathGame::~MentalMathGame()
{
	qDebug() << "destructor";
	std::ofstream progress("1_x.txt");
	for (size_t i = 0; i < 10; i++)
	{
		progress << score[i][0];
		for (size_t j = 1; j < 10; j++)
		{
			progress << " " << score[i][j];
		}
		if (i < 9) progress << std::endl;
		delete[] score[i];
	}
}

void MentalMathGame::generateEquation()
{	
	/* initialize random seed: */
	srand(time(NULL));
	/* generate numbers between 0 and 9: */
	n1 = rand() % 9;
	n2 = rand() % 9;

	ui.equation->setText(QString::number(n1) + "x" + QString::number(n2));
	ui.answer->setText("");
}

void MentalMathGame::saveProgress()
{
	score[n1][n2] += 1;
}

void MentalMathGame::loadProgress()
{
	std::ifstream progress("1_x.txt");
	std::string line;
	if (progress.is_open())
	{
		for (size_t i = 0; i < 10; i++)
		{
			std::getline(progress, line);
			qDebug() << line;
			score[i] = splitString(line);
		}
		progress.close();
	}
}

int *MentalMathGame::splitString(std::string s)
{
	std::stringstream ss(s);
	std::string n;
	int *scoreLine = new int[10];
	for (size_t i = 0; i < 10; i++)
	{
		ss >> n;
		scoreLine[i] = stoi(n);
	}
	return scoreLine;
}

void MentalMathGame::keyPressEvent(QKeyEvent* pe)
{
	if (pe->key() == Qt::Key_Return || pe->key() == Qt::Key_Enter) checkAnswer();
}

void MentalMathGame::checkAnswer() {
	qDebug() << "checkAnswer";
	int answer = n1 * n2;
	bool flag;
	if (QString::compare(ui.answer->text(), "", Qt::CaseInsensitive) == 0) {
		flag = false;
	}
	else {
		qDebug() << "correct answer: " << answer;
		qDebug() << "typed answer: " << ui.answer->text().toInt();
		flag = ui.answer->text().toInt() == answer;
		if (flag) {
			saveProgress();
		}
	}

	ui.feedback->setText(flag ? "Correct! Play it again!" : "Wrong! Try again!");
	generateEquation();
}