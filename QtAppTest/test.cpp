#include "pch.h"

TEST(MentalMath, Constructor) {
	Controller* control = Controller::getInstance("C:/Users/rodol/Documents/Python projects/MindTrainer/QtApp/settings.json");
	EXPECT_TRUE(control != nullptr);

	std::string digitsN1 = control->getMentalMathSettings("n1");
	std::string digitsN2 = control->getMentalMathSettings("n2");

	MentalMath mm = MentalMath();

	EXPECT_EQ(digitsN1, mm.getDigitsN1());
	EXPECT_EQ(digitsN2, mm.getDigitsN2());
}