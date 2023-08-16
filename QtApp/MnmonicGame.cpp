#include "MnmonicGame.h"

MnmonicGame::MnmonicGame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(ui.checkButton, SIGNAL(clicked()), this, SLOT(checkClicked()));
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
	connect(ui.scoreButton, SIGNAL(clicked()), this, SLOT(showScore()));

	generateDigits();
	loadProgress();
}

MnmonicGame::~MnmonicGame()
{
	qDebug() << "destructor";
	std::ofstream progress("mnmonic.txt");
	progress << score[0];
	for (size_t i = 1; i < 110; i++)
	{
		progress << " " << score[i];
	}
}

int* MnmonicGame::getScore()
{
	return score;
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
		if (list[i].size() == 2) score[list[i].toInt()] += 1;
		else if (list[i].size() == 1) score[list[i].toInt() + 100] += 1;
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

void MnmonicGame::showScore()
{
	Dialog* diag = new Dialog(this, this);
	diag->show();
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

Dialog::Dialog(QWidget* parent, MnmonicGame* game):
	QDialog(parent)
{
	game = game;
	ui.setupUi(this);
	QBoxLayout *layouts[11];
	layouts[0] = ui.column_0;
	layouts[1] = ui.column_1;
	layouts[2] = ui.column_2;
	layouts[3] = ui.column_3;
	layouts[4] = ui.column_4;
	layouts[5] = ui.column_5;
	layouts[6] = ui.column_6;
	layouts[7] = ui.column_7;
	layouts[8] = ui.column_8;
	layouts[9] = ui.column_9;
	layouts[10] = ui.column_10;
	for (size_t i = 0; i < 11; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			QLabel* label = new QLabel();
			if (i < 10) label->setText(QString::number(i) + QString::number(j) + ": " + QString::number(game->getScore()[i*10+j]));
			else if (i == 10) label->setText(QString::number(j) + ": " + QString::number(game->getScore()[i*10+j]));
			layouts[i]->addWidget(label);
		}
	}
}
