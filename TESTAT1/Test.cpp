#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "pocketcalculator.h"
#include "sevensegment.h"
#include "calc.h"

void test_sevensegment_digitOne() {
	std::ostringstream test{};
	printLargeDigit(1,test);
	ASSERT_EQUAL("   \n  |\n   \n  |\n   \n", test.str());
}

void test_sevensegment_digitTwo() {
	std::ostringstream test{};
	printLargeDigit(2,test);
	ASSERT_EQUAL(" - \n  |\n - \n|  \n - \n", test.str());
}

void test_sevensegment_digitThree() {
	std::ostringstream test{};
	printLargeDigit(3,test);
	ASSERT_EQUAL(" - \n  |\n - \n  |\n - \n", test.str());
}

void test_sevensegment_digitFour() {
	std::ostringstream test{};
	printLargeDigit(4,test);
	ASSERT_EQUAL("   \n| |\n - \n  |\n   \n", test.str());
}

void test_sevensegment_digitFive() {
	std::ostringstream test{};
	printLargeDigit(5,test);
	ASSERT_EQUAL(" - \n|  \n - \n  |\n - \n", test.str());
}

void test_sevensegment_digitSix() {
	std::ostringstream test{};
	printLargeDigit(6,test);
	ASSERT_EQUAL(" - \n|  \n - \n| |\n - \n", test.str());
}

void test_sevensegment_digitSeven() {
	std::ostringstream test{};
	printLargeDigit(7,test);
	ASSERT_EQUAL(" - \n  |\n   \n  |\n   \n", test.str());
}

void test_sevensegment_digitEight() {
	std::ostringstream test{};
	printLargeDigit(8,test);
	ASSERT_EQUAL(" - \n| |\n - \n| |\n - \n", test.str());
}

void test_sevensegment_digitNine() {
	std::ostringstream test{};
	printLargeDigit(9,test);
	ASSERT_EQUAL(" - \n| |\n - \n  |\n   \n", test.str());
}

void test_sevensegment_digitNull() {
	std::ostringstream test{};
	printLargeDigit(0,test);
	ASSERT_EQUAL(" - \n| |\n   \n| |\n - \n", test.str());
}

void test_sevensegment_largeNumberOneOneOne() {
	std::ostringstream test{};
	printLargeNumber(111,test);
	ASSERT_EQUAL("         \n  |  |  |\n         \n  |  |  |\n         \n", test.str());
}

void test_sevensegment_largeNumber4567() {
	std::ostringstream test{};
	printLargeNumber(4567,test);
	ASSERT_EQUAL("    -  -  - \n| ||  |    |\n -  -  -    \n  |  || |  |\n    -  -    \n", test.str());
}

void test_sevensegment_printError() {
	std::ostringstream test{};
	printError(test);
	ASSERT_EQUAL(" -             \n|              \n -  -  -  -  - \n|  |  |  | ||  \n -        -    \n", test.str());
}

void test_calc_one_plus_one() {
	auto result = calc(1, 1, '+');
	ASSERT_EQUAL(2, result);
}

void test_calc_two_minus_one() {
	auto result = calc(2, 1, '-');
	ASSERT_EQUAL(1, result);
}

void test_calc_two_times_three() {
	auto result = calc(2, 3, '*');
	ASSERT_EQUAL(6, result);
}

void test_calc_five_divided_two() {
	auto result = calc(5, 2, '/');
	ASSERT_EQUAL(2, result);
}

void test_calc_wrong_operator() {
	ASSERT_THROWS(calc(5, 2, 'h'),std::logic_error);
}

void test_calc_division_by_zero() {
	ASSERT_THROWS(calc(5, 0, '/'),std::logic_error);
}

void test_calc_stream_correct() {
	std::istringstream stream {"4 + 5"};
	int result = calc(stream);
	ASSERT_EQUAL(9, result);
}

void test_calc_stream_fail() {
	std::istringstream stream {"4 h 5"};
	ASSERT_THROWS(calc(stream),std::logic_error);
}

void test_calc_overflow_addition() {
	std::istringstream stream {"2147483647 + 2147483647"};
	ASSERT_THROWS(calc(stream),std::logic_error);
}

void test_calc_overflow_mutliplication() {
	std::istringstream stream {"2147483647 * 2147483647"};
	ASSERT_THROWS(calc(stream),std::logic_error);
}

void test_pocketcalculator_normal() {
	std::ostringstream test{};
	std::istringstream input{"3567+1000"};
	pocketcalculator(input,test);
	ASSERT_EQUAL("    -  -  - \n| ||  |    |\n -  -  -    \n  |  || |  |\n    -  -    \n", test.str());
}

void test_pocketcalculator_tolarge_output() {
	std::ostringstream test{};
	std::istringstream input{"10000*10000"};
	pocketcalculator(input,test);
	ASSERT_EQUAL(" -             \n|              \n -  -  -  -  - \n|  |  |  | ||  \n -        -    \n", test.str());

}

void test_pocketcalculator_divison_zero() {
	std::ostringstream test{};
	std::istringstream input{"10000/0"};
	pocketcalculator(input,test);
	ASSERT_EQUAL(" -             \n|              \n -  -  -  -  - \n|  |  |  | ||  \n -        -    \n", test.str());
}

void test_pocketcalculator_modulo_zero() {
	std::ostringstream test{};
	std::istringstream input{"10%0"};
	pocketcalculator(input,test);
	ASSERT_EQUAL(" -             \n|              \n -  -  -  -  - \n|  |  |  | ||  \n -        -    \n", test.str());
}

void test_pocketcalculator_adition_overflow() {
	std::ostringstream test{};
	std::istringstream input{"2147483647 + 2147483647"};
	pocketcalculator(input,test);
	ASSERT_EQUAL(" -             \n|              \n -  -  -  -  - \n|  |  |  | ||  \n -        -    \n", test.str());
}

void test_pocketcalculator_multiplication_overflow() {
	std::ostringstream test{};
	std::istringstream input{"2147483647 * 2147483647"};
	pocketcalculator(input,test);
	ASSERT_EQUAL(" -             \n|              \n -  -  -  -  - \n|  |  |  | ||  \n -        -    \n", test.str());
}

void test_pocketcalculator_invalid_operator() {
	std::ostringstream test{};
	std::istringstream input{"2 h 6"};
	pocketcalculator(input,test);
	ASSERT_EQUAL(" -             \n|              \n -  -  -  -  - \n|  |  |  | ||  \n -        -    \n", test.str());
}

void test_pocketcalculator_invalid_input() {
	std::ostringstream test{};
	std::istringstream input{"26"};
	pocketcalculator(input,test);
	ASSERT_EQUAL(" -             \n|              \n -  -  -  -  - \n|  |  |  | ||  \n -        -    \n", test.str());
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_sevensegment_digitOne));
	s.push_back(CUTE(test_sevensegment_digitTwo));
	s.push_back(CUTE(test_sevensegment_digitThree));
	s.push_back(CUTE(test_sevensegment_digitFour));
	s.push_back(CUTE(test_sevensegment_digitFive));
	s.push_back(CUTE(test_sevensegment_digitSix));
	s.push_back(CUTE(test_sevensegment_digitSeven));
	s.push_back(CUTE(test_sevensegment_digitEight));
	s.push_back(CUTE(test_sevensegment_digitNine));
	s.push_back(CUTE(test_sevensegment_digitNull));
	s.push_back(CUTE(test_sevensegment_largeNumberOneOneOne));
	s.push_back(CUTE(test_sevensegment_largeNumber4567));
	s.push_back(CUTE(test_sevensegment_printError));
	s.push_back(CUTE(test_calc_one_plus_one));
	s.push_back(CUTE(test_calc_two_minus_one));
	s.push_back(CUTE(test_calc_two_times_three));
	s.push_back(CUTE(test_calc_five_divided_two));
	s.push_back(CUTE(test_calc_wrong_operator));
	s.push_back(CUTE(test_calc_division_by_zero));
	s.push_back(CUTE(test_calc_stream_correct));
	s.push_back(CUTE(test_calc_stream_fail));
	s.push_back(CUTE(test_calc_overflow_addition));
	s.push_back(CUTE(test_calc_overflow_mutliplication));
	s.push_back(CUTE(test_pocketcalculator_normal));
	s.push_back(CUTE(test_pocketcalculator_tolarge_output));
	s.push_back(CUTE(test_pocketcalculator_divison_zero));
	s.push_back(CUTE(test_pocketcalculator_modulo_zero));
	s.push_back(CUTE(test_pocketcalculator_adition_overflow));
	s.push_back(CUTE(test_pocketcalculator_multiplication_overflow));
	s.push_back(CUTE(test_pocketcalculator_invalid_operator));
	s.push_back(CUTE(test_pocketcalculator_invalid_input));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
