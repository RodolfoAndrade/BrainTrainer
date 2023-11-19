#pragma once

#include <QMainWindow>
#include "ui_MnmonicGame.h"
#include <QDebug>
#include <QKeyEvent>
#include "Mnmonic.h"

class MnmonicGame : public QMainWindow
{
	Q_OBJECT

public:
	MnmonicGame(QWidget *parent = nullptr);
	~MnmonicGame();
	void start();

private:
	Mnmonic mnm;
	Ui::MnmonicGameClass ui;

private slots:
	void okClicked();
	void checkClicked();
	void valueChanged();

protected:
	void keyPressEvent(QKeyEvent* pe);
};