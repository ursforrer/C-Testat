/*
 * pocketcalculator.cpp
 *
 *  Created on: 13.10.2016
 *      Author: hsr
 */
#include "pocketcalculator.h"
#include <iostream>
#include <sstream>
#include <string>
#include "calc.h"
#include "sevensegment.h"

void pocketcalculator(std::istream &in, std::ostream &out) {
	std::string line;
	int result{};
	while(std::getline(in, line)) {
		std::istringstream linestream{line};
		try {
			result = calc(linestream);
			printLargeNumber(result, out);
		}
		catch (std::logic_error const &e) {
			printError(out);
		}
	}
}



