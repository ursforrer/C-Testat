#ifndef KWIC_H_
#define KWIC_H_

#include "vector"
#include "istream"
#include "set"
#include "word.h"

std::vector<std::vector<word::Word>> getWords(std::istream &is);
std::vector<word::Word> getWordsPerLine(std::string input);
void kwic(std::istream &is, std::ostream &out);
std::set<std::vector<word::Word>> rotate(std::vector<std::vector<word::Word>> lines);
void print(std::set<std::vector<word::Word>> rotatedLines, std::ostream &out);

#endif /* KWIC_H_ */
