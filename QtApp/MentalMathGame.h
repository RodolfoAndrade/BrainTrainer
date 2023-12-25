#pragma once

#include <QMainWindow>
#include "ui_MentalMathGame.h"
#include <QDebug>
#include <QKeyEvent>
#include "MentalMath.h"
#include <QThread>

class MentalMathGame : public QMainWindow
{
	Q_OBJECT

public:
	MentalMathGame(QWidget *parent = nullptr);
	~MentalMathGame();

private:
	Ui::MentalMathGameClass ui;
	MentalMath math;

private slots:
	void checkAnswer();
	void start();
	void errorString(QString err);
	void setBar(int x);

protected:
	void keyPressEvent(QKeyEvent* pe);
};

class Worker : public QObject {
	Q_OBJECT
public:
	Worker();
	~Worker();
public slots:
	void process();
signals:
	void finished();
	void error(QString err);
	void setBar(int x);
private:
	// add your variables here
};