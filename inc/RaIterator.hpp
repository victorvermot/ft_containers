#ifndef RAITERATOR_H
# define RAITERATOR_H

# include <iostream>
# include "Iterator.hpp"

template <typename T>
class RaIterator {

private:
	T *_ptr;

public:
	RaIterator<T>() : _ptr(NULL) { return ; }
	explicit RaIterator<T>(T &value) : _ptr(&value) { return ; }
	RaIterator<T>(const RaIterator& other) {
		*this = other;
	}

	RaIterator& operator=(const RaIterator& rhs) {
		this->_ptr = rhs._ptr;
		return (*this);
	}

	T& operator*() const { return *_ptr; }
	T* operator->() const { return _ptr; }
	T& operator[](int index) { return _ptr[index]; }

	RaIterator& operator++() {
		_ptr++;
		return (*this);
	}

	RaIterator operator++(int) {
		RaIterator temp = *this;
		++(*this);
		return (temp);
	}

	RaIterator& operator--() {
		_ptr--;
		return (*this);
	}

	RaIterator operator--(int) {
		RaIterator temp = *this;
		--(*this);
		return (temp);
	}

	RaIterator& operator+=(int n) {
		this->_ptr += n;
		return (*this);
	}

	RaIterator& operator-=(unsigned int n) {
		this->_ptr -= n;
		return (*this);
	}

	RaIterator operator+(unsigned int n) {
		RaIterator temp = *this;
		temp += n;
		return (temp);
	}

	RaIterator operator-(unsigned int n) {
		RaIterator temp = *this;
		temp -= n;
		return (temp);
	}

	friend RaIterator& operator-(RaIterator& lhs, const RaIterator& rhs) {
		lhs -= rhs;
		return (lhs);
	}

	friend RaIterator operator+(int lhs, RaIterator rhs) {
		RaIterator temp = rhs;
		temp += lhs;
		return (temp);
	}

	friend bool operator>=(const RaIterator& a, const RaIterator& b) { return a._ptr >= b._ptr; }
	friend bool operator<=(const RaIterator& a, const RaIterator& b) { return a._ptr <= b._ptr; }
	friend bool operator<(const RaIterator& a, const RaIterator& b) { return a._ptr < b._ptr; }
	friend bool operator>(const RaIterator& a, const RaIterator& b) { return a._ptr > b._ptr; }
	friend bool operator==(const RaIterator& a, const RaIterator& b) { return a._ptr == b._ptr; }
	friend bool operator!=(const RaIterator& a, const RaIterator& b) { return a._ptr != b._ptr; }
	~RaIterator<T>() {};
};

#endif
