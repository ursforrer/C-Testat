#ifndef INDEXABLESET_H_
#define INDEXABLESET_H_
//TODO: Add the implementation of your indexableSet here

#include <set>
#include <iterator>
#include <stdexcept>

template <typename T, class Comparator = std::less<T>>
class indexableSet
:public std::set<T, Comparator>{
	using Base=std::set<T, Comparator>;

public:
	using std::set<T, Comparator>::set;

	T const & at(int index) const {
		int size = this->size();
		if(index < size && index >= (-size)){
			if(index < 0){
				index += size;
			}
			auto it {this->begin()};
			std::advance(it, index);
			return *it;
		} else {
			throw std::out_of_range("Index out of Bound");
		}
	}

	T const & operator[](int index) const {
		return this->at(index);
	}

	T const & front() const {
		return this->at(0);
	}

	T const & back() const {
			return this->at(this->size()-1);
		}

};



#endif /* INDEXABLESET_H_ */
