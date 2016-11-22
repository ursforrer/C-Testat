#include "word.h"
#include "algorithm"
#include "iterator"
#include "string"
#include "stdexcept"

namespace word{

	bool Word::isValidWord(std::string s) {
		// Link to Reference http://en.cppreference.com/w/cpp/algorithm/all_any_none_of
		// Link to Reference http://www.cplusplus.com/reference/string/string/empty/
		bool result{};
		result = std::all_of(s.begin(), s.end(), [](char c){ return std::isalpha(c);});
		// String darf ja auch nicht leer sein.
		return result && !s.empty();

	}

	// Konstruktor
	Word::Word(std::string text) : text{text}{
		if (!isValidWord(text)) {
			throw std::out_of_range{"invalid word"};
		}
	}

	bool Word::operator <(Word const& rhs) const {
		// Vergleich von Strings
		// Link to Reference http://en.cppreference.com/w/cpp/algorithm/lexicographical_compare (Found with Google)
		// Schema for the Function std::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
		// Ignoring Lettercase wird mit dem Comparator abgefangen
		// To Lower http://en.cppreference.com/w/cpp/string/byte/tolower (Found with Google)
		bool result{};
		// Kommentar aus der Erstellung ==> Compare auf Wordobjekt selbst geht nicht. Es muss auf dem String passieren.
		result = std::lexicographical_compare(std::begin(this->text), std::end(this->text), std::begin(rhs.text), std::end(rhs.text), [](char a, char b) {
			return std::tolower(a) < std::tolower(b);
		});
		return result;
	}


}


