#pragma once
#include <QDebug>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class Controller
{
private:
	nlohmann::json j;
public:
	Controller();
	std::string getMentalMathSettings();
};

