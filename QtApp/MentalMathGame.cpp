#include "MentalMathGame.h"

MentalMathGame::MentalMathGame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.checkButton, SIGNAL(clicked()), this, SLOT(checkAnswer()));
	connect(ui.numberDigits, SIGNAL(currentTextChanged(QString)), this, SLOT(restart()));

	generateEquation();
	loadProgress();
}

MentalMathGame::~MentalMathGame()
{
	qDebug() << "destructor";
	QString text = ui.numberDigits->currentText();
	std::ofstream progress;
	int n = 10;
	if (text.compare("1") == 0) {
		progress.open("1_x.txt");
		n = 10;
	}
	else if (text.compare("2") == 0) {
		progress.open("2_x.txt");
		n = 100;
	}
	for (size_t i = 0; i < n; i++)
	{
		progress << score[i][0];
		for (size_t j = 1; j < n; j++)
		{
			progress << " " << score[i][j];
		}
		if (i < n-1) progress << std::endl;
		delete[] score[i];
	}
	delete[] score;
}

void MentalMathGame::generateEquation()
{	
	QString text = ui.numberDigits->currentText();
	int n = 9;
	if (text.compare("1") == 0) n = 9;
	else if (text.compare("2") == 0) n = 99;

	/* initialize random seed: */
	srand(time(NULL));
	/* generate numbers between 0 and 9: */
	n1 = rand() % n;
	n2 = rand() % n;

	ui.equation->setText(QString::number(n1) + "x" + QString::number(n2));
	ui.answer->setText("");
	ui.answer->setFocus();
}

void MentalMathGame::saveProgress()
{
	score[n1][n2] += 1;
}

void MentalMathGame::loadProgress()
{
	QString text = ui.numberDigits->currentText();
	std::ifstream progress;
	int n = 10;
	if (text.compare("1") == 0) {
		progress.open("1_x.txt");
		n = 10;
	}
	else if (text.compare("2") == 0) {
		progress.open("2_x.txt");
		n = 100;
	}
	
	std::string line;
	if (progress.is_open())
	{
		score = new int*[n];
		for (size_t i = 0; i < n; i++)
		{
			std::getline(progress, line);
			qDebug() << line;
			score[i] = splitString(line, n);
		}
		progress.close();
	}
}

int *MentalMathGame::splitString(std::string s, int n)
{
	std::stringstream ss(s);
	std::string var;
	int *scoreLine = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		ss >> var;
		scoreLine[i] = stoi(var);
	}
	return scoreLine;
}

void MentalMathGame::restart()
{
	// delete previous score
	if (score != nullptr) {
		QString text = ui.numberDigits->currentText();
		int n = 10;
		if (text.compare("1") == 0) {
			n = 100;
		}
		else if (text.compare("2") == 0) {
			n = 10;
		}
		for (size_t i = 0; i < n; i++)
		{
			delete[] score[i];
		}
		delete[] score;
	}
	generateEquation();
	loadProgress();
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
		flag = ui.answer->text().toInt() == answer;
		if (flag) {
			saveProgress();
		}
	}
	ui.correctAnswer->setText("Correct answer : " + QString::number(answer));
	ui.givenAnswer->setText("Given answer: " + ui.answer->text());
	ui.feedback->setText(flag ? "Correct! Play it again!" : "Wrong! Try again!");
	generateEquation();
}