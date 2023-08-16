#pragma once

#include <QMainWindow>
#include "ui_MentalMathGame.h"
#include <QDebug>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QKeyEvent>
#include <iostream>
#include <fstream>
#include <sstream>

class MentalMathGame : public QMainWindow
{
	Q_OBJECT

public:
	MentalMathGame(QWidget *parent = nullptr);
	~MentalMathGame();

private:
	Ui::MentalMathGameClass ui;
	int n1;
	int n2;
	void generateEquation();
	int *score[10];
	void saveProgress();
	void loadProgress();
	int *splitString(std::string s);

private slots:
	void checkAnswer();

protected:
	void keyPressEvent(QKeyEvent* pe);
};
