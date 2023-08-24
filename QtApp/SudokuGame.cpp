#include "SudokuGame.h"

SudokuGame::SudokuGame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	openGames();

	for (int i = 1; i <= 9 * 9; i++) {
		QString name = QStringLiteral("button_%1").arg(i);
		QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
		if(game[i - 1]!='0') button->setText(QString(game[i - 1]));
		else button->setText("");
	}
}

SudokuGame::~SudokuGame()
{}

void SudokuGame::openGames()
{
	std::ifstream sudokuGames("sudoku.csv"); //has 1000000 games
	std::string line;
	int n, pos, length;

	//choose a random game
	srand(time(NULL));
	n = rand() % 1000000;

	if (sudokuGames.is_open()) {
		getline(sudokuGames, line); //get header
		pos = line.size()+1;
		getline(sudokuGames, line); //get first game
		length = line.size()+1; //+1 for the /n
		sudokuGames.seekg(pos+n*length); //2 gets 4rd, n gets n+2 game
		getline(sudokuGames, line); //get 3rd game
		game = line.substr(0, 81);
		solution = line.substr(81+1,81);
	}
}
