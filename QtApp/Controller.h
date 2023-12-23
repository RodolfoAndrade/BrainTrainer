#pragma once
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class Controller
{
private:
	Controller(nlohmann::json j);
	static Controller* control;
	static nlohmann::json j;
public:
	static Controller* getInstance(std::string filename);
	static std::string getMentalMathSettings(std::string n);
	static std::string getMnmonicSettings();
};