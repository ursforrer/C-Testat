#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "kwic.h"
#include "word.h"

void test_createSimpleWord() {
	// Test Method Word Creation and Print
	word::Word w{"Urs"};
	std::ostringstream os {};
	w.print(os);
	ASSERT_EQUAL("Urs",os.str());
}

void test_InputValid() {
	std::istringstream is{"Urs"};
	word::Word w{};
	std::ostringstream os {};
	is >> w;
	w.print(os);
	ASSERT_EQUAL("Urs",os.str());
}

void test_InputInValid() {
	// Wieso genau funktioniert dieser Test nicht.
	std::istringstream is{"87213721387"};
	word::Word w{};
	std::ostringstream os {};
	is >> w;
	ASSERT(is.fail());
}

void test_createErrorWords_Numbers() {
	// Test Method Word Konstruktor
	ASSERT_THROWS((word::Word {"777"}),std::out_of_range);
}

void test_createErrorWords_TwoandNumbers() {
	// Test Method Word Konstruktor
	ASSERT_THROWS((word::Word {"777 asbdsa"}),std::out_of_range);
}

void test_createErrorWords_Two() {
	// Test Method Word Konstruktor
	ASSERT_THROWS((word::Word {"Urs Forrer"}),std::out_of_range);
}

void test_createErrorWords_Tab() {
	// Test Method Word Konstruktor
	ASSERT_THROWS((word::Word {"	"}),std::out_of_range);
}

void test_createEmptyWord() {
	// Test Method Word Konstruktor
	ASSERT_THROWS((word::Word {""}),std::out_of_range);
}

void test_isValid() {
	// Test Method isValid
	ASSERT(word::Word::isValidWord("Urs"));
}

void test_isValid_Invalid() {
	// Test Method isValid
	ASSERT(!word::Word::isValidWord("Urs Forrer"));
	ASSERT(!word::Word::isValidWord(" "));
	ASSERT(!word::Word::isValidWord("	"));
	ASSERT(!word::Word::isValidWord("7dd77"));
}

void test_WordEqual() {
	word::Word w{"Urs"};
	ASSERT(w == w);
}

void test_WordEqual_DiffrentCases() {
	word::Word w1{"Urs"};
	word::Word w2{"urs"};
	ASSERT(w1 == w2);
	ASSERT(!(w1 != w2));
}
void test_WordEqual_Not() {
	word::Word w1{"Urs"};
	word::Word w2{"urt"};
	ASSERT(w1 != w2);
	ASSERT(!(w1 == w2));
}

void test_WordLessThan() {
	word::Word w1{"aab"};
	word::Word w2{"Aac"};
	ASSERT(w1 < w2);
	ASSERT(!(w2 < w1));
}

void test_WordLessThanOrEqual() {
	word::Word w1{"aab"};
	word::Word w2{"Aab"};
	word::Word w3{"Aac"};
	ASSERT(w1 <= w2);
	ASSERT(w1 <= w3);
	ASSERT(w2 <= w1);
	ASSERT(!(w3 <= w1));
}

void test_WordGreaterThan() {
	word::Word w1{"aab"};
	word::Word w2{"Aac"};
	ASSERT(w2 > w1);
	ASSERT(!(w1 > w2));
}

void test_WordGreaterThanOrEqual() {
	word::Word w1{"aab"};
	word::Word w2{"Aab"};
	word::Word w3{"Aac"};
	ASSERT(w2 >= w1);
	ASSERT(w3 >= w1);
	ASSERT(w1 >= w2);
	ASSERT(!(w1 >= w3));
}

void test_kwic_getWordsPerLine() {
	std::string test{"this is a test"};
	std::vector<word::Word> testvector {word::Word{"this"},word::Word{"is"},word::Word{"a"},word::Word{"test"}};
	ASSERT_EQUAL(testvector, getWordsPerLine(test));
}

void test_kwic_getWordsPerLine_Empty() {
	std::string test{""};
	std::vector<word::Word> testvector {};
	ASSERT_EQUAL(testvector, getWordsPerLine(test));
}

void test_kwic_getWords_singleLine() {
	std::istringstream test{"this is a test\n"};
	std::vector<word::Word> testvector1 {word::Word{"this"},word::Word{"is"},word::Word{"a"},word::Word{"test"}};
	std::vector<std::vector<word::Word>> testvector3 {testvector1};
	std::vector<std::vector<word::Word>> testvector4 = getWords(test);
	ASSERT_EQUAL(testvector3, testvector4);
}

void test_kwic_getWords_multiLine() {
	std::istringstream test{"this is a test\nthis is another test\n"};
	std::vector<word::Word> testvector1 {word::Word{"this"},word::Word{"is"},word::Word{"a"},word::Word{"test"}};
	std::vector<word::Word> testvector2 {word::Word{"this"},word::Word{"is"},word::Word{"another"},word::Word{"test"}};
	std::vector<std::vector<word::Word>> testvector3 {testvector1, testvector2};
	std::vector<std::vector<word::Word>> testvector4 = getWords(test);
	ASSERT_EQUAL(testvector3, testvector4);
}

void test_kwic_getWords_empty() {
	std::istringstream test{""};
	std::vector<std::vector<word::Word>> testvector3 {};
	std::vector<std::vector<word::Word>> testvector4 = getWords(test);
	ASSERT_EQUAL(testvector3, testvector4);
}

void test_kwic_whole_system_singleline() {
	std::ostringstream out{};
	std::istringstream input{"Die HSR ist toll\n"};
	kwic(input,out);
	ASSERT_EQUAL("\nDie HSR ist toll \nHSR ist toll Die \nist toll Die HSR \ntoll Die HSR ist ", out.str());
}

void test_kwic_whole_system_multiline() {
	std::istringstream input{"Die HSR ist toll\nWir sind so gut\n"};
	std::ostringstream out{};
	kwic(input, out);
	ASSERT_EQUAL("\nDie HSR ist toll \ngut Wir sind so \nHSR ist toll Die \nist toll Die HSR \nsind so gut Wir \nso gut Wir sind \ntoll Die HSR ist \nWir sind so gut ", out.str());
}

void test_kwic_whole_system_empty() {
	std::istringstream input{""};
	std::ostringstream out{};
	kwic(input, out);
	ASSERT_EQUAL("", out.str());
}

void test_kwic_whole_system_numbers() {
	std::istringstream input{"1627 822727 2193219323"};
	std::ostringstream out{};
	kwic(input, out);
	ASSERT_EQUAL("", out.str());
}

void test_kwic_rotate() {
	std::vector<word::Word> testvector {word::Word{"this"},word::Word{"is"},word::Word{"a"},word::Word{"test"}};
	std::vector<std::vector<word::Word>> input {testvector};

	std::vector<word::Word> testvector_comp1 {word::Word{"a"},word::Word{"test"},word::Word{"this"},word::Word{"is"}};
	std::vector<word::Word> testvector_comp2 {word::Word{"is"},word::Word{"a"},word::Word{"test"},word::Word{"this"}};
	std::vector<word::Word> testvector_comp3 {word::Word{"test"},word::Word{"this"},word::Word{"is"},word::Word{"a"}};
	std::vector<word::Word> testvector_comp4 {word::Word{"this"},word::Word{"is"},word::Word{"a"},word::Word{"test"}};

	std::set<std::vector<word::Word>> output_to_compare{};
	output_to_compare.insert(testvector_comp1);
	output_to_compare.insert(testvector_comp2);
	output_to_compare.insert(testvector_comp3);
	output_to_compare.insert(testvector_comp4);

	ASSERT_EQUAL(output_to_compare, rotate(input));
}

void test_kwic_rotate_empty() {
	std::vector<std::vector<word::Word>> input {};
	std::set<std::vector<word::Word>> output_to_compare{};
	ASSERT_EQUAL(output_to_compare, rotate(input));
}

void test_kwic_print() {
	std::vector<word::Word> testvector_comp1 {word::Word{"a"},word::Word{"test"},word::Word{"this"},word::Word{"is"}};
	std::vector<word::Word> testvector_comp2 {word::Word{"is"},word::Word{"a"},word::Word{"test"},word::Word{"this"}};
	std::vector<word::Word> testvector_comp3 {word::Word{"test"},word::Word{"this"},word::Word{"is"},word::Word{"a"}};
	std::vector<word::Word> testvector_comp4 {word::Word{"this"},word::Word{"is"},word::Word{"a"},word::Word{"test"}};

	std::set<std::vector<word::Word>> input{};
	input.insert(testvector_comp1);
	input.insert(testvector_comp2);
	input.insert(testvector_comp3);
	input.insert(testvector_comp4);

	std::ostringstream output{};

	print(input, output);
	ASSERT_EQUAL("\na test this is \nis a test this \ntest this is a \nthis is a test ", output.str());
}

void test_kwic_print_empty() {
	std::set<std::vector<word::Word>> input{};
	std::ostringstream output{};
	print(input, output);
	ASSERT_EQUAL("", output.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(test_createSimpleWord));
	s.push_back(CUTE(test_InputValid));
	s.push_back(CUTE(test_InputInValid));
	s.push_back(CUTE(test_createErrorWords_Numbers));
	s.push_back(CUTE(test_createErrorWords_TwoandNumbers));
	s.push_back(CUTE(test_createErrorWords_Two));
	s.push_back(CUTE(test_createErrorWords_Tab));
	s.push_back(CUTE(test_createEmptyWord));
	s.push_back(CUTE(test_isValid));
	s.push_back(CUTE(test_isValid_Invalid));
	s.push_back(CUTE(test_WordEqual));
	s.push_back(CUTE(test_WordEqual_DiffrentCases));
	s.push_back(CUTE(test_WordEqual_Not));
	s.push_back(CUTE(test_WordLessThan));
	s.push_back(CUTE(test_WordLessThanOrEqual));
	s.push_back(CUTE(test_WordGreaterThan));
	s.push_back(CUTE(test_WordGreaterThanOrEqual));
	s.push_back(CUTE(test_kwic_getWordsPerLine));
	s.push_back(CUTE(test_kwic_getWordsPerLine_Empty));
	s.push_back(CUTE(test_kwic_getWords_singleLine));
	s.push_back(CUTE(test_kwic_getWords_multiLine));
	s.push_back(CUTE(test_kwic_getWords_empty));
	s.push_back(CUTE(test_kwic_whole_system_singleline));
	s.push_back(CUTE(test_kwic_whole_system_multiline));
	s.push_back(CUTE(test_kwic_whole_system_empty));
	s.push_back(CUTE(test_kwic_whole_system_numbers));
	s.push_back(CUTE(test_kwic_rotate));
	s.push_back(CUTE(test_kwic_rotate_empty));
	s.push_back(CUTE(test_kwic_print));
	s.push_back(CUTE(test_kwic_print_empty));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
