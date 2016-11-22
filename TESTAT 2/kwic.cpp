#include "word.h"
#include "vector"
#include "istream"
#include "set"
#include "iterator"
#include "algorithm"
#include "sstream"
#include "string"

std::vector<word::Word> getWordsPerLine(std::string input) {
	std::istringstream bla (input);
	using it = std::istream_iterator<word::Word>;
	std::vector<word::Word> words (it{bla}, it{});
	return words;
}


std::vector<std::vector<word::Word>> getWords(std::istream &is) {
	std::vector<std::vector<word::Word>> lines{};
	std::string line;
	while(std::getline(is, line)) {
		std::vector<word::Word> wordsPerLine = getWordsPerLine(line);
		lines.push_back(wordsPerLine);
	}
	return lines;
}


std::set<std::vector<word::Word>> rotate(std::vector<std::vector<word::Word>> lines) {
	std::set<std::vector<word::Word>> rotatedLines{};
	std::for_each(std::begin(lines), std::end(lines), [&rotatedLines](std::vector<word::Word> line) {
		std::vector<word::Word> temp{};
		for (auto it = std::begin(line); it != std::end(line);it++) {
			temp.clear();
			std::rotate_copy(line.begin(), it, line.end(), std::back_inserter(temp));
			rotatedLines.insert(temp);
		}
	});

	return rotatedLines;
}

void print(std::set<std::vector<word::Word>> rotatedLines, std::ostream &out) {
	std::for_each(std::begin(rotatedLines), std::end(rotatedLines), [&out](std::vector<word::Word> rotatedLine) {
		out << "\n";
		std::copy(rotatedLine.begin(), rotatedLine.end(), std::ostream_iterator<word::Word>(out, " "));
	});
}

void kwic(std::istream &is, std::ostream &out) {
	std::vector<std::vector<word::Word>> lines{getWords(is)};
	print(rotate(lines), out);
}




