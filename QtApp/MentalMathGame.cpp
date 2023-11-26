#include "MentalMathGame.h"

MentalMathGame::MentalMathGame(QWidget *parent)
	: QMainWindow(parent), math{ MentalMath() }
{
	qDebug() << "MentalMathGame constructor";

	// setting up ui and buttons
	ui.setupUi(this);
	connect(ui.checkButton, SIGNAL(clicked()), this, SLOT(checkAnswer()));

	// get index of dropdown type of mentalmath, which shows the number of digits
	int index = ui.n1->findText(QString::fromStdString(math.getDigitsN1()));
	if (index != -1) ui.n1->setCurrentIndex(index);
	index = ui.n2->findText(QString::fromStdString(math.getDigitsN2()));
	if (index != -1) ui.n2->setCurrentIndex(index);

	// disconnecting combbox to set up value without emitting signal
	connect(ui.n1, SIGNAL(currentTextChanged(QString)), this, SLOT(start()));
	connect(ui.n2, SIGNAL(currentTextChanged(QString)), this, SLOT(start()));

	start();
}

MentalMathGame::~MentalMathGame()
{
	qDebug() << "destructor";
}

void MentalMathGame::start()
{
	// set number of digits
	math.setNumberDigits(ui.n1->currentText().toStdString(), ui.n2->currentText().toStdString());
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