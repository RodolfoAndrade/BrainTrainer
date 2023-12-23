#include "pch.h"

TEST(MentalMath, controller) {
	Controller* control = Controller::getInstance("C:/Users/rodol/Documents/Python projects/MindTrainer/QtApp/settings.json");
	EXPECT_TRUE(control != nullptr);

	std::string digitsN1 = control->getMentalMathSettings("n1");
	std::string digitsN2 = control->getMentalMathSettings("n2");

	MentalMath mm = MentalMath();

	EXPECT_EQ(digitsN1, mm.getDigitsN1());
	EXPECT_EQ(digitsN2, mm.getDigitsN2());
}

TEST(MentalMath, generateEquation) {
	MentalMath mm = MentalMath();

	EXPECT_TRUE(mm.getN1() != -842150451);
	EXPECT_TRUE(mm.getN2() != -842150451);
}

TEST(MentalMath, setNumberDigits) {
	MentalMath mm = MentalMath();
	mm.setNumberDigits("8888", "8888");

	EXPECT_EQ("8888", mm.getDigitsN1());
	EXPECT_EQ("8888", mm.getDigitsN2());
}

TEST(MentalMath, getAnswer) {
	MentalMath mm = MentalMath();
	mm.setNumberDigits("8888", "8888");

	EXPECT_EQ(mm.getN1() * mm.getN2(), mm.getAnswer());
}