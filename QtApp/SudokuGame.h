#pragma once

#include <QMainWindow>
#include "ui_SudokuGame.h"
#include <QDialog>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class SudokuGame : public QMainWindow
{
	Q_OBJECT

public:
	SudokuGame(QWidget *parent = nullptr);
	~SudokuGame();

private:
	Ui::SudokuGameClass ui;
	void openGames();
	std::string game, solution;
};
