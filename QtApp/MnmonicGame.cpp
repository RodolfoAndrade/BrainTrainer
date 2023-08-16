#include "MnmonicGame.h"

MnmonicGame::MnmonicGame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(ui.checkButton, SIGNAL(clicked()), this, SLOT(checkClicked()));
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));

	generateDigits();
	loadProgress();
}

MnmonicGame::~MnmonicGame()
{
	qDebug() << "destructor";
	std::ofstream progress("mnmonic.txt");
	progress << score[0];
	for (size_t i = 0; i < 109; i++)
	{
		progress << " " << score[i];
	}
}

void MnmonicGame::generateDigits()
{
	QString digits;
	int n;

	/* initialize random seed: */
	srand(time(NULL));

	for (size_t i = 0; i < ui.spinBox->value(); i++)
	{
		/* generate secret number between 0 and 9: */
		n = rand() % 9;
		if (i != 0 && i % 2 == 0) digits += "-";
		digits += QString::number(n);
	}

	ui.digits->setFocus();
	ui.digits->setText(digits);
	ui.okButton->setVisible(true);
	ui.checkButton->setVisible(false);
}

void MnmonicGame::saveProgress()
{
	QString digits;
	auto list = ui.digits->text().split("-");
	for (size_t i = 0; i < list.size(); i++)
	{
		score[list[i].toInt()] += 1;
	}
}

void MnmonicGame::splitString(std::string s)
{
	std::stringstream ss(s);
	std::string n;
	for (size_t i = 0; i < 110; i++)
	{
		ss >> n;
		score[i] = stoi(n);
	}
}

void MnmonicGame::loadProgress()
{
	std::ifstream progress("mnmonic.txt");
	std::string line;
	if (progress.is_open()) {
		while (std::getline(progress, line)) {
			splitString(line);
		}
	}
}

void MnmonicGame::checkClicked()
{
	bool flag = QString::compare(digits, ui.digits->text(), Qt::CaseInsensitive) == 0;
	if (flag) saveProgress();
	ui.answer->setText(flag ? "Correct! Play it again!" : "Wrong! Try again!");
	ui.correctAnswer->setText("Correct answer: " + digits);
	ui.givenAnswer->setText("Given answer: " + ui.digits->text());
	generateDigits();
}

void MnmonicGame::valueChanged()
{
	generateDigits();
}

void MnmonicGame::keyPressEvent(QKeyEvent* pe)
{
	if (pe->key() == Qt::Key_Return || pe->key() == Qt::Key_Enter) {
		if (ui.okButton->isVisible()) okClicked();
		else if (ui.checkButton->isVisible()) checkClicked();
	}
}

void MnmonicGame::okClicked()
{
	digits = ui.digits->text();
	ui.digits->setFocus();
	ui.digits->setText("");
	ui.okButton->setVisible(false);
	ui.checkButton->setVisible(true);
}
