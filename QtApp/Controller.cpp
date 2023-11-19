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

std::string Controller::getMentalMathSettings()
{
    return j["MentalMath"];
}

std::string Controller::getMnmonicSettings()
{
    return j["Mnmonic"];
}
