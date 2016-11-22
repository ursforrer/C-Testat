#ifndef WORD_H_
#define WORD_H_

#include "string"
#include "istream"
#include "ostream"

namespace word{

	class Word {
		// Variablen
		std::string text;

		public:
			// Default Konstruktor
			Word() = default;
			// Konstruktordefklaration
			Word(std::string text);

			// Read Member Methode
			std::istream & read(std::istream & is) {
				std::string text{};
				// Überspringen, solange es keine zulässigen Zeichen sind
				while(!isalpha(is.peek()) && !is.eof()) {
					is.get();
				}
				// Alle Zeichen abfüllen, bis wieder ein zuzulässiges Zeichen kommt.
				while(isalpha(is.peek())) {
					text += is.get();
				}

				// Wort definitiv abspeichern
				// Und falls es kein Wort ist, wird der Konstruktor eine Exception werfen
				try {
					Word input{text};
					(*this) = input;
					is.clear();
				}
				catch (std::out_of_range & e) {
					is.setstate(std::ios::failbit | is.rdstate());
				}
				// Stream zurückgeben um weiterfahren zu können
				return is;
			}

			// Print Member Methode
			std::ostream & print(std::ostream & os) const {
				os << text;
				return os;
			}
			static bool isValidWord(std::string s);

			// Gemäss Datebeispiel
			bool operator <(Word const& rhs) const;
		private:

	};

	// Input Operator Methode, so dass richtig darauf zugeriffen werden kann
	inline std::istream & operator>>(std::istream & is, Word & word) {
		return word.read(is);
	}

	// Output Operator Metthode, so dass richtig darauf zugeriffen werden kann
	inline std::ostream & operator<<(std::ostream & os, Word const & word) {
		return word.print(os);
	}

	// Operatoren gemäss Datebeispiel
	inline bool operator>(Word const& lhs, Word const& rhs) {
		return rhs < lhs;
	}

	inline bool operator>=(Word const& lhs, Word const& rhs) {
		return !(lhs < rhs);
	}

	inline bool operator<=(Word const& lhs, Word const& rhs) {
		return !(rhs < lhs);
	}

	inline bool operator==(Word const& lhs, Word const& rhs) {
		return !(lhs < rhs) && !(rhs < lhs);
	}

	inline bool operator!=(Word const& lhs, Word const& rhs) {
		return !(lhs == rhs);
	}


}


#endif /* WORD_H_ */
