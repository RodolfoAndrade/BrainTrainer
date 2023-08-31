#include "SudokuGame.h"

SudokuGame::SudokuGame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.newGameButton, SIGNAL(clicked()), this, SLOT(newGame()));
	for (int i = 1; i <= 9 * 9; i++) {
		QString name = QStringLiteral("button_%1").arg(i);
		QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
		connect(button, SIGNAL(clicked()), this, SLOT(clickedCell()));
	}
	for (int i = 1; i <= 9; i++) {
		QString name = QStringLiteral("selectButton_%1").arg(i);
		QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
		connect(button, SIGNAL(clicked()), this, SLOT(clickedSelect()));
		button->setEnabled(false);
	}
	ui.annotateButton->setCheckable(true);
	connect(ui.annotateButton, SIGNAL(clicked()), this, SLOT(clickedAnnotate()));
	normal = ui.button_1->palette();
	red = ui.button_1->palette();
	blue = ui.button_1->palette();
	red.setColor(QPalette::ButtonText, Qt::red);
	blue.setColor(QPalette::ButtonText, Qt::blue);

	newGame();
}

SudokuGame::~SudokuGame()
{}

bool SudokuGame::check(QPushButton** toggled)
{
	int n;

	while (!redButtons.isEmpty()) {
		QPushButton *button = redButtons.back();
		button->setPalette(normal);
		redButtons.pop_back();
	}

	QString name = (*toggled)->objectName();
	n = name.split('_')[1].toInt();

	//check row
	int row = (n-1) / 9;
	//check col
	int col = (n - 1) % 9;

	//check square
	for (int i = (row/3)*3; i < (row/3)*3+3; i++) {
		for (int j = (col/3)*3+1; j < (col / 3) * 3 + 4; j++) {
			QString name = QStringLiteral("button_%1").arg(i * 9 + j);
			QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
			if (button!=(*toggled)&&button->text().compare((*toggled)->text()) == 0) {
				button->setPalette(red);
				(*toggled)->setPalette(red);
				redButtons.push_back(button);
				//return false;
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		QString name = QStringLiteral("button_%1").arg(i * 9 + col+1);
		QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
		if (button != (*toggled) && button->text().compare((*toggled)->text()) == 0) {
			button->setPalette(red);
			(*toggled)->setPalette(red);
			redButtons.push_back(button);
			//return false;
		}
	}
	for (int i = 1; i <= 9; i++) {
		QString name = QStringLiteral("button_%1").arg(row * 9 + i);
		QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
		if (button != (*toggled) && button->text().compare((*toggled)->text()) == 0) {
			button->setPalette(red);
			(*toggled)->setPalette(red);
			redButtons.push_back(button);
			//return false;
		}
	}
	if ((*toggled)->palette() != red) {
		if (solution[row * 9 + col] == (*toggled)->text()) {
			(*toggled)->setPalette(blue);
			(*toggled)->setCheckable(false);
			(*toggled) = nullptr;
		}
		return true;
	}
	else return false;
}

void SudokuGame::clickedCell()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (ui.annotateButton->isChecked()==false&&button->isCheckable()&& toggled != button) {
		if (toggled != nullptr) {
			toggled->setChecked(false);
			if (toggled->palette() == red) {
				toggled->setPalette(normal);
				toggled->setText("");

				while (!redButtons.isEmpty()) {
					QPushButton* button = redButtons.back();
					button->setPalette(normal);
					redButtons.pop_back();
				}
			}
		}
		toggled = button;
	}
	if (ui.annotateButton->isChecked() && selected != nullptr) {
		toggled = button;
		toggled->setText(selected->text());
		check(&toggled);
	}
}

void SudokuGame::clickedSelect()
{
	if (toggled != nullptr && toggled->palette() == red) {
		toggled->setPalette(normal);
		toggled->setText("");

		while (!redButtons.isEmpty()) {
			QPushButton* button = redButtons.back();
			button->setPalette(normal);
			redButtons.pop_back();
		}
	}
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (ui.annotateButton->isChecked() && selected != button) {
		if (selected != nullptr) {
			selected->setChecked(false);
		}
		selected = button;
	}
}

void SudokuGame::clickedAnnotate()
{
	if (toggled!=nullptr&&toggled->palette() == red) {
		toggled->setPalette(normal);
		toggled->setText("");

		while (!redButtons.isEmpty()) {
			QPushButton* button = redButtons.back();
			button->setPalette(normal);
			redButtons.pop_back();
		}
	}
	if (ui.annotateButton->isChecked()==false) {
		if (selected) selected->setChecked(false);
		for (int i = 1; i <= 9; i++) {
			QString name = QStringLiteral("selectButton_%1").arg(i);
			QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
			button->setCheckable(false);
			button->setEnabled(false);
		}
		for (int i = 1; i <= 9 * 9; i++) {
			QString name = QStringLiteral("button_%1").arg(i);
			QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
			if (button->text() != "") button->setCheckable(true);
		}
	}
	else {
		if (toggled) toggled->setChecked(false);
		for (int i = 1; i <= 9; i++) {
			QString name = QStringLiteral("selectButton_%1").arg(i);
			QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
			button->setCheckable(true);
			button->setEnabled(true);
		}
		for (int i = 1; i <= 9 * 9; i++) {
			QString name = QStringLiteral("button_%1").arg(i);
			QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
			if(button->text()=="") button->setCheckable(false);
		}
		selected = ui.selectButton_1;
		selected->setChecked(true);
	}
}

void SudokuGame::keyPressEvent(QKeyEvent* pe)
{
	if (toggled != nullptr&&ui.annotateButton->isChecked()==false) {
		if (pe->key() == Qt::Key_1) {
			toggled->setText("1");
		}
		else if (pe->key() == Qt::Key_2) {
			toggled->setText("2");
		}
		else if (pe->key() == Qt::Key_3) {
			toggled->setText("3");
		}
		else if (pe->key() == Qt::Key_4) {
			toggled->setText("4");
		}
		else if (pe->key() == Qt::Key_5) {
			toggled->setText("5");
		}
		else if (pe->key() == Qt::Key_6) {
			toggled->setText("6");
		}
		else if (pe->key() == Qt::Key_7) {
			toggled->setText("7");
		}
		else if (pe->key() == Qt::Key_8) {
			toggled->setText("8");
		}
		else if (pe->key() == Qt::Key_9) {
			toggled->setText("9");
		}
		check(&toggled);
	}
	if (ui.annotateButton->isChecked()) {
		if (selected)selected->setChecked(false);
		if (pe->key() == Qt::Key_1) {
			selected = ui.selectButton_1;
		}
		else if (pe->key() == Qt::Key_2) {
			selected = ui.selectButton_2;
		}
		else if (pe->key() == Qt::Key_3) {
			selected = ui.selectButton_3;
		}
		else if (pe->key() == Qt::Key_4) {
			selected = ui.selectButton_4;
		}
		else if (pe->key() == Qt::Key_5) {
			selected = ui.selectButton_5;
		}
		else if (pe->key() == Qt::Key_6) {
			selected = ui.selectButton_6;
		}
		else if (pe->key() == Qt::Key_7) {
			selected = ui.selectButton_7;
		}
		else if (pe->key() == Qt::Key_8) {
			selected = ui.selectButton_8;
		}
		else if (pe->key() == Qt::Key_9) {
			selected = ui.selectButton_9;
		}
		selected->setChecked(true);
	}
}

void SudokuGame::newGame()
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

	sudokuGames.close();

	for (int i = 1; i <= 9 * 9; i++) {
		QString name = QStringLiteral("button_%1").arg(i);
		QPushButton* button = ui.centralWidget->findChild<QPushButton*>(name);
		button->setPalette(normal);
		if (game[i - 1] != '0') {
			button->setText(QString(game[i - 1]));
			if (button->isCheckable()) button->setCheckable(false);
		}
		else {
			button->setText("");
			if (!button->isCheckable()) {
				button->setCheckable(true);
			}
			else {
				button->setChecked(false);
			}
		}
	}
}
