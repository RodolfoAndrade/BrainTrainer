#pragma once

#include <QMainWindow>
#include "ui_MnmonicGame.h"
#include <QDebug>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QKeyEvent>
#include <iostream>
#include <fstream>
#include <sstream>

class MnmonicGame : public QMainWindow
{
	Q_OBJECT

public:
	MnmonicGame(QWidget *parent = nullptr);
	~MnmonicGame();

private:
	int digitsLength = 4;
	QString digits;
	Ui::MnmonicGameClass ui;
	void generateDigits();
	int score[110];
	void saveProgress();
	void loadProgress();
	void splitString(std::string s);

private slots:
	void okClicked();
	void checkClicked();
	void valueChanged();

protected:
	void keyPressEvent(QKeyEvent* pe);
};
