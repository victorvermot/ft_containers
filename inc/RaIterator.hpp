#ifndef RAITERATOR_H
# define RAITERATOR_H

# include <iostream>
# include "Iterator.hpp"

namespace ft {
	class random_access_iterator_tag {};
}

template <typename T>
class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {

private:
	T *_ptr;
public:

	random_access_iterator<T>() : _ptr(NULL) { return ; }
	explicit random_access_iterator<T>(T &value) : _ptr(&value) { return ; }
	random_access_iterator<T>(const random_access_iterator& other) {
		*this = other;
	}

	random_access_iterator& operator=(const random_access_iterator& rhs) {
		this->_ptr = rhs._ptr;
		return (*this);
	}

	T& operator*() const { return *_ptr; }
	T* operator->() const { return _ptr; }
	T& operator[](int index) { return _ptr[index]; }

	random_access_iterator& operator++() {
		_ptr++;
		return (*this);
	}

	random_access_iterator operator++(int) {
		random_access_iterator temp = *this;
		++(*this);
		return (temp);
	}

	random_access_iterator& operator--() {
		_ptr--;
		return (*this);
	}

	random_access_iterator operator--(int) {
		random_access_iterator temp = *this;
		--(*this);
		return (temp);
	}

	random_access_iterator& operator+=(int n) {
		this->_ptr += n;
		return (*this);
	}

	random_access_iterator& operator-=(unsigned int n) {
		this->_ptr -= n;
		return (*this);
	}

	random_access_iterator operator+(unsigned int n) {
		random_access_iterator temp = *this;
		temp += n;
		return (temp);
	}

	random_access_iterator operator-(unsigned int n) {
		random_access_iterator temp = *this;
		temp -= n;
		return (temp);
	}

	friend std::ptrdiff_t operator-(random_access_iterator& lhs, const random_access_iterator& rhs) {
		return (lhs._ptr - rhs._ptr);
	}

	friend std::ptrdiff_t operator-(const random_access_iterator& lhs, const random_access_iterator& rhs) {
		return (lhs._ptr - rhs._ptr);
	}

	friend std::ptrdiff_t operator+(const random_access_iterator& lhs, const random_access_iterator& rhs) {
		return (lhs._ptr + rhs._ptr);
	}

	friend std::ptrdiff_t operator+(random_access_iterator& lhs, random_access_iterator& rhs) {
		return (lhs._ptr + rhs._ptr);
	}

	friend random_access_iterator operator+(int lhs, random_access_iterator rhs) {
		random_access_iterator temp = rhs;
		temp += lhs;
		return (temp);
	}

	friend bool operator>=(const random_access_iterator& a, const random_access_iterator& b) { return a._ptr >= b._ptr; }
	friend bool operator<=(const random_access_iterator& a, const random_access_iterator& b) { return a._ptr <= b._ptr; }
	friend bool operator<(const random_access_iterator& a, const random_access_iterator& b) { return a._ptr < b._ptr; }
	friend bool operator>(const random_access_iterator& a, const random_access_iterator& b) { return a._ptr > b._ptr; }
	friend bool operator==(const random_access_iterator& a, const random_access_iterator& b) { return a._ptr == b._ptr; }
	friend bool operator!=(const random_access_iterator& a, const random_access_iterator& b) { return a._ptr != b._ptr; }
	~random_access_iterator<T>() {};
};

#endif
