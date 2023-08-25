#pragma once

#include <QMainWindow>
#include "ui_SudokuGame.h"
#include <QDialog>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QKeyEvent>

class SudokuGame : public QMainWindow
{
	Q_OBJECT

public:
	SudokuGame(QWidget *parent = nullptr);
	~SudokuGame();

private:
	Ui::SudokuGameClass ui;
	std::string game, solution;
	QPushButton* toggled = nullptr;
	QList<QPushButton*> redButtons;
	bool check(QPushButton** toggled);
	QPalette normal;
	QPalette blue;
	QPalette red;

private slots:
	void newGame();
	void clickedCell();

protected:
	void keyPressEvent(QKeyEvent* pe);
};
