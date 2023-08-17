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
	int ni = 10;
	int nj = 10;
	if (text.compare("1") == 0) {
		progress.open("1_x.txt");
		ni = 10;
		nj = 10;
	}
	else if (text.compare("2") == 0) {
		progress.open("2_x.txt");
		ni = 100;
		nj = 100;
	}
	else if (text.compare("1.2") == 0) {
		progress.open("1.2_x.txt");
		ni = 10;
		nj = 100;
	}
	for (size_t i = 0; i < ni; i++)
	{
		progress << score[i][0];
		for (size_t j = 1; j < nj; j++)
		{
			progress << " " << score[i][j];
		}
		if (i < ni-1) progress << std::endl;
	}
}

void MentalMathGame::generateEquation()
{	
	QString text = ui.numberDigits->currentText();
	int n = 9;

	//if full digits
	if (text.compare("1") == 0 || text.compare("2") == 0) {
		if (text.compare("1") == 0) n = 9;
		else if (text.compare("2") == 0) n = 99;

		/* initialize random seed: */
		srand(time(NULL));
		/* generate numbers between 0 and 9: */
		n1 = rand() % n;
		n2 = rand() % n;
	}
	else {
		if (text.compare("1.2") == 0) {
			n1 = rand() % 9;
			n2 = rand() % 99;
		}
	}

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
	int ni = 10;
	int nj = 10;
	if (text.compare("1") == 0) {
		progress.open("1_x.txt");
		ni = 10;
		nj = 10;
	}
	else if (text.compare("2") == 0) {
		progress.open("2_x.txt");
		ni = 100;
		nj = 100;
	}
	else if (text.compare("1.2") == 0) {
		progress.open("1.2_x.txt");
		ni = 10;
		nj = 100;
	}
	
	std::string line;
	if (progress.is_open())
	{
		for (size_t i = 0; i < ni; i++)
		{
			std::getline(progress, line);
			qDebug() << line;
			score.push_back(splitString(line, nj));
		}
		progress.close();
	}
}

std::vector<int> MentalMathGame::splitString(std::string s, int n)
{
	std::stringstream ss(s);
	std::string var;
	std::vector<int> scoreLine(n, 0);
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
	score.clear();
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