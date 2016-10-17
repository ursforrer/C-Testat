/*
 * sevensegment.cpp
 *
 *  Created on: 07.10.2016
 *      Author: hsr
 */
#include "sevensegment.h"
#include <ostream>
#include <vector>
#include <iterator>
#include <algorithm>

std::vector<std::vector<std::string>> const digits {
{" - ", "   ", " - ", " - ","   "," - "," - "," - "," - "," - "},
{"| |", "  |", "  |", "  |","| |","|  ","|  ","  |","| |","| |"},
{"   ", "   ", " - ", " - "," - "," - "," - ","   "," - "," - "},
{"| |", "  |", "|  ", "  |","  |","  |","| |","  |","| |","  |"},
{" - ", "   ", " - ", " - ","   "," - "," - ","   "," - ","   "}
};

std::vector<std::vector<std::string>> const error {
{" - ", "   ", "   ", "   ","   "},
{"|  ", "   ", "   ", "   ","   "},
{" - ", " - ", " - ", " - "," - "},
{"|  ", "|  ", "|  ", "| |","|  "},
{" - ", "   ", "   ", " - ","   "}
};

void printError(std::ostream &out) {
	std::string number = "01234";
	for_each(begin(error), end(error),[&](auto line){
		for_each(begin(number), end(number),[&](auto x){
			out << line[x - '0'];
		});
		out << '\n';
	});
}

void printLargeDigit(int i, std::ostream &out) {
	for_each(begin(digits), end(digits),[&](auto x){
		out << x[i] << '\n';
	});
}

void printLargeNumber(int i, std::ostream &out) {
	std::string number = std::to_string(i);
	for_each(begin(digits), end(digits),[&](auto line){
		for_each(begin(number), end(number),[&](auto x){
			out << line[x - '0'];
		});
		out << '\n';
	});

}






