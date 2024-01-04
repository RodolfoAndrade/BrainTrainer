#include "pch.h"

TEST(MentalMath, controller) {
	Controller* control = Controller::getInstance("C:/Users/rodol/Documents/Python projects/BrainTrainer/QtApp/settings.json");
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

TEST(MentalMath, getAnswerDefault) {
	MentalMath mm = MentalMath();
	
	mm.setNumberDigits("8888", "8888");

	EXPECT_EQ(mm.getN1() * mm.getN2(), mm.getAnswer());
}

TEST(MentalMath, getAnswerAdd) {
	MentalMath mm = MentalMath();

	bool ops[] = { true, false, false, false };
	mm.setOperations(ops, 1);

	EXPECT_EQ(mm.getN1() + mm.getN2(), mm.getAnswer());
}

TEST(MentalMath, getAnswerSub) {
	MentalMath mm = MentalMath();

	bool ops[] = { false, true, false, false };
	mm.setOperations(ops, 1);

	EXPECT_EQ(mm.getN1() - mm.getN2(), mm.getAnswer());
}

TEST(MentalMath, getAnswerMul) {
	MentalMath mm = MentalMath();

	bool ops[] = { false, false, true, false };
	mm.setOperations(ops, 1);

	EXPECT_EQ(mm.getN1() * mm.getN2(), mm.getAnswer());
}

TEST(MentalMath, getAnswerDiv) {
	MentalMath mm = MentalMath();

	bool ops[] = { false, false, false, true };
	mm.setOperations(ops, 1);

	EXPECT_EQ(mm.getN1() / mm.getN2(), mm.getAnswer());
}

TEST(MentalMath, getOperator) {
	MentalMath mm = MentalMath();

	bool ops[] = { true, true, false, false };
	mm.setOperations(ops, 2);

	EXPECT_TRUE(mm.getOperation() == '+' || mm.getOperation() == '-');
}

TEST(MentalMath, thread) {
	int argc = 1;
	char* args[] = { (char*)"QtApp" };
	QApplication a(argc, args);

	MentalMathGame mmg = MentalMathGame();

	EXPECT_FALSE(mmg.getThread().isNull());
}