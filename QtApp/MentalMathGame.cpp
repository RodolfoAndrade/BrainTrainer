#include "MentalMathGame.h"

MentalMathGame::MentalMathGame(QWidget *parent)
	: QMainWindow(parent), math{ MentalMath() }
{
	qDebug() << "MentalMathGame constructor";

	// setting up ui and buttons
	ui.setupUi(this);
	connect(ui.checkButton, SIGNAL(clicked()), this, SLOT(checkAnswer()));
	connect(ui.numberDigits, SIGNAL(currentTextChanged(QString)), this, SLOT(start()));

	// get index of dropdown type of mentalmath, which shows the number of digits
	int index = ui.numberDigits->findText(QString::fromStdString(math.getNumberDigits()));
	if (index != -1) ui.numberDigits->setCurrentIndex(index);

	start();
}

MentalMathGame::~MentalMathGame()
{
	qDebug() << "destructor";
}

void MentalMathGame::start()
{
	// set number of digits
	math.setNumberDigits(ui.numberDigits->currentText().toStdString());
	// create equation
	math.generateEquation();
	// update ui to display equation
	ui.equation->setText(QString::number(math.getN1()) + "x" + QString::number(math.getN2()));
	ui.answer->setText("");
	ui.answer->setFocus();
}

void MentalMathGame::keyPressEvent(QKeyEvent* pe)
{
	if (pe->key() == Qt::Key_Return || pe->key() == Qt::Key_Enter) checkAnswer();
}

void MentalMathGame::checkAnswer() {
	qDebug() << "checkAnswer";

	int answer = math.getAnswer();
	bool flag;

	// if text is empty
	if (QString::compare(ui.answer->text(), "", Qt::CaseInsensitive) == 0) {
		flag = false;
	}
	else {
		flag = ui.answer->text().toInt() == answer;
	}
	// set up feedback
	ui.correctAnswer->setText("Correct answer : " + QString::number(answer));
	ui.givenAnswer->setText("Given answer: " + ui.answer->text());
	ui.feedback->setText(flag ? "Correct! Play it again!" : "Wrong! Try again!");
	// restart
	start();
}