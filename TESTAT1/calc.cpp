/*
 * calc.cpp
 *
 *  Created on: 30.09.2016
 *      Author: hsr
 */
#include "calc.h"
#include <limits>
#include <istream>

int const maxDigitSize{8};

int calc(int lhs, int rhs , char op) {
	int result{0};
	switch(op) {
	case '+' :
		if ((std::numeric_limits<int>::max() - lhs) < rhs) {
			throw std::logic_error{"Addition Overflow"};
		}
		result = lhs + rhs;
		break;
	case '/' :
		if (rhs == 0) {
			throw std::logic_error{"Division by Zero"};
		}
		result = lhs / rhs;
		break;
	case '-' :
		result = lhs - rhs;
		break;
	case '*' :
		if ((std::numeric_limits<int>::max() / lhs) < rhs) {
			throw std::logic_error{"Multiplication Overflow"};
		}
		result = lhs * rhs;
		break;
	case '%' :
		if (rhs == 0) {
			throw std::logic_error{"Modulo by Zero"};
		}
		result = lhs % rhs;
		break;
	default :
		throw std::logic_error{"Invalid Operator"};
	}
	return result;
}

int calc(std::istream& in) {
	int result{};
	int lhs{};
	int rhs{};
	char op{};
	in >> lhs;
	in >> op;
	if (in >> rhs) {
		result = calc(lhs, rhs, op);
		if (std::to_string(result).length() > maxDigitSize) {
			throw std::logic_error{"Too Large Output"};
		}
		return result;
	}
	else {
		throw std::logic_error{"Invalid Input"};
	}
}



