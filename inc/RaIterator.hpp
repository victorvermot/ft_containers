#ifndef RAITERATOR_H
# define RAITERATOR_H

# include <iostream>
# include "Iterator.hpp"

template <typename T>
class RaIterator {

private:
	T *_ptr;
public:
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::random_access_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;
//	typedef typename T::iterator_category iterator_category;
//	typedef typename T::value_type        value_type;
//	typedef typename T::difference_type   difference_type;
//	typedef typename T::pointer           pointer;
//	typedef typename T::reference         reference;
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

	friend std::ptrdiff_t operator-(RaIterator& lhs, const RaIterator& rhs) {
		return (lhs._ptr - rhs._ptr);
	}

	friend std::ptrdiff_t operator+(const RaIterator& lhs, const RaIterator& rhs) {
		return (lhs._ptr + rhs._ptr);
	}

	friend std::ptrdiff_t operator+(RaIterator& lhs, RaIterator& rhs) {
		return (lhs._ptr + rhs._ptr);
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
