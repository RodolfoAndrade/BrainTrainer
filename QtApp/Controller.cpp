#include "Controller.h"

Controller::Controller() {
    qDebug() << "Controller constructor";

    std::ifstream file("./settings.json");
    file >> j;
}

std::string Controller::getMentalMathSettings()
{
    return j["MentalMath"];
}
