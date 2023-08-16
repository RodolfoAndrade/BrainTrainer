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
#include <QDialog>
#include "ui_MnmonicScore.h"

class MnmonicGame : public QMainWindow
{
	Q_OBJECT

public:
	MnmonicGame(QWidget *parent = nullptr);
	~MnmonicGame();
	int* getScore();

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
	void showScore();

protected:
	void keyPressEvent(QKeyEvent* pe);
};

class Dialog : public QDialog, public Ui::MnmonicScoreDialog
{
public:
	Dialog(QWidget* parent, MnmonicGame* game);
private:
	MnmonicGame* game;
	Ui::MnmonicScoreDialog ui;
};