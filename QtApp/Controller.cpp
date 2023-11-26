#include "Controller.h"

Controller* Controller::control = nullptr;
nlohmann::json Controller::j;

Controller::Controller(nlohmann::json i) {
    j = i;
}

Controller* Controller::getInstance()
{
    if (control == nullptr) {
        nlohmann::json i;
        std::ifstream file("./settings.json");
        file >> i;
        control = new Controller(i);
    }
    return control;
}

std::string Controller::getMentalMathSettings(std::string n)
{
    if (n.compare("n1") == 0) {
        return j["MentalMath"]["n1"];
    }
    else if (n.compare("n2") == 0) {
        return j["MentalMath"]["n2"];
    }
}

std::string Controller::getMnmonicSettings()
{
    return j["Mnmonic"];
}
