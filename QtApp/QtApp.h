#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtApp.h"
#include <QDebug>
#include "MentalMathGame.h"
#include "MnmonicGame.h"
#include "SudokuGame.h"

class QtApp : public QMainWindow
{
    Q_OBJECT

public:
    QtApp(QWidget *parent = nullptr);
    ~QtApp();

private:
    Ui::QtAppClass ui;
    MentalMathGame *mentalMathGame = nullptr;
    MnmonicGame *mnmonicGame = nullptr;
    SudokuGame *sudokuGame = nullptr;

private slots:
    void openMentalMathGame();
    void openMnmonicGame();
    void openSudokuGame();
};
