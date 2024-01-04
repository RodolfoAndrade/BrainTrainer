#include "MnmonicGame.h"

MnmonicGame::MnmonicGame(QWidget *parent)
	: QMainWindow(parent), mnm{Mnmonic()}
{
	// setting up ui and buttons
	ui.setupUi(this);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(ui.checkButton, SIGNAL(clicked()), this, SLOT(checkClicked()));
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));

	ui.spinBox->setValue(mnm.getDigitsLength());
	start();
}

MnmonicGame::~MnmonicGame()
{
	qDebug() << "destructor";
}

void MnmonicGame::start()
{
	// generate sequence of digits
	mnm.generateDigits(ui.spinBox->value());
	ui.digits->setFocus();
	ui.digits->setText(QString::fromStdString(mnm.getDigits()));
	ui.label_3->setText("Digits to be memorized:");
	ui.okButton->setVisible(true);
	ui.checkButton->setVisible(false);
}

void MnmonicGame::checkClicked()
{
	bool flag = QString::compare(QString::fromStdString(mnm.getDigits()), ui.digits->text(), Qt::CaseInsensitive) == 0;
	ui.answer->setText(flag ? "Correct! Play it again!" : "Wrong! Try again!");
	ui.correctAnswer->setText("Correct answer: " + QString::fromStdString(mnm.getDigits()));
	ui.givenAnswer->setText("Given answer: " + ui.digits->text());
	start();
}

void MnmonicGame::valueChanged()
{
	start();
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
	ui.digits->setFocus();
	ui.digits->setText("");
	ui.label_3->setText("Digits memorized:");
	ui.okButton->setVisible(false);
	ui.checkButton->setVisible(true);
}