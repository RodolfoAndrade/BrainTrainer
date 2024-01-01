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
	connect(ui.addCheckBox, SIGNAL(stateChanged(int)), this, SLOT(start()));
	connect(ui.subCheckBox, SIGNAL(stateChanged(int)), this, SLOT(start()));
	connect(ui.mulCheckBox, SIGNAL(stateChanged(int)), this, SLOT(start()));
	connect(ui.divCheckBox, SIGNAL(stateChanged(int)), this, SLOT(start()));
	connect(ui.timeoutSpinBox, SIGNAL(valueModified()), this, SLOT(start()));

	start();
}

MentalMathGame::~MentalMathGame()
{
	qDebug() << "MentalMathGame destructor";
}

void MentalMathGame::start()
{
	if (thread) {
		if (thread->isRunning()) {
			thread->requestInterruption();
			thread->quit();
		}
	}
	// set number of digits
	math.setNumberDigits(ui.n1->currentText().toStdString(), ui.n2->currentText().toStdString());
	// create equation
	math.generateEquation();
	// set timeout
	timeout = ui.timeoutSpinBox->value();
	// update ui to display equation
	ui.equation->setText(QString::number(math.getN1()) + "x" + QString::number(math.getN2()));
	ui.answer->setText("");
	ui.answer->setFocus();
	// set up worker
	thread = new QThread();
	Worker* worker = new Worker(timeout);
	worker->moveToThread(thread);
	connect(worker, &Worker::error, this, &MentalMathGame::errorString);
	connect(worker, &Worker::setBar, this, &MentalMathGame::setBar);
	connect(thread, &QThread::started, worker, &Worker::process);
	connect(worker, &Worker::finished, thread, &QThread::quit);
	connect(worker, &Worker::finished, worker, &Worker::deleteLater);
	connect(thread, &QThread::finished, thread, &QThread::deleteLater);
	thread->start();
}

void MentalMathGame::errorString(QString err)
{
	qDebug() << "errorString:" << err;
}

void MentalMathGame::setBar(int x)
{
	auto bar = ui.progressBar;
	bar->setValue(x);
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

Worker::Worker(int timeout)
{
	this->timeout = timeout;
}

Worker::~Worker()
{
}

void Worker::process() { // Process. Start processing data.
	// allocate resources using new here
	qDebug("starting worker process");
	clock_t start = clock();
	clock_t shortStart = start;
	int value = 0;
	do {
		if ((float)(clock() - shortStart) / CLOCKS_PER_SEC > ((float)timeout)/100.0) {
			shortStart = clock();
			value += 1;
			emit setBar(value);
		}
	} while ((float)(clock() - start) / CLOCKS_PER_SEC < ((float)timeout) && !QThread::currentThread()->isInterruptionRequested());
	emit setBar(100);
	emit finished();
}