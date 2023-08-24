#include "QtApp.h"

QtApp::QtApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.mentalMathButton, SIGNAL(clicked()), this, SLOT(openMentalMathGame()));
    connect(ui.mnmonicButton, SIGNAL(clicked()), this, SLOT(openMnmonicGame()));
    connect(ui.sudokuButton, SIGNAL(clicked()), this, SLOT(openSudokuGame()));
}

QtApp::~QtApp()
{
    if (mentalMathGame != nullptr) delete mentalMathGame;
    if (mnmonicGame != nullptr) delete mnmonicGame;
}

void QtApp::openMentalMathGame()
{
    qDebug() << "openMentalMathGame";
    mentalMathGame = new MentalMathGame(this);
    mentalMathGame->show();
}

void QtApp::openMnmonicGame()
{
    qDebug() << "openMnmonicGame";
    mnmonicGame = new MnmonicGame(this);
    mnmonicGame->show();
}

void QtApp::openSudokuGame()
{
    qDebug() << "openSudokuGame";
    sudokuGame = new SudokuGame(this);
    sudokuGame->show();
}
