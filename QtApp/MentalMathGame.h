#pragma once

#include <QMainWindow>
#include "ui_MentalMathGame.h"
#include <QDebug>
#include <QKeyEvent>
#include "MentalMath.h"

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

protected:
	void keyPressEvent(QKeyEvent* pe);
};
