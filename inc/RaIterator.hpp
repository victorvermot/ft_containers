#ifndef RAITERATOR_H
# define RAITERATOR_H

# include <iostream>
# include "Iterator.hpp"
# include "enable_if.hpp"

namespace ft {

	// Category of random access iterator
	class random_access_iterator_tag {};

	// Random access iterator class for vector
	template<typename T>
	class random_access_iterator {

	public:

		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef random_access_iterator_tag iterator_category;

	private:

		pointer _ptr;

	public:

		random_access_iterator() : _ptr(NULL) {}

		explicit random_access_iterator(pointer ptr) : _ptr(ptr) {}
//		template <typename Y>
//		explicit random_access_iterator(const random_access_iterator<Y>& other) : _ptr(other._ptr) {}
//		explicit random_access_iterator(const random_access_iterator<const value_type> &other) : _ptr(other._ptr) {}

		random_access_iterator(const random_access_iterator &other) {
			*this = other;
		}

		random_access_iterator &operator=(const random_access_iterator &rhs) {
			this->_ptr = rhs._ptr;
			return (*this);
		}

//		template<bool Q = Const>
//		typename ft::enable_if<Q, const T &>::type operator*() { return *_ptr; }
//
//		template<bool Q = Const>
//		typename ft::enable_if<!Q, T &>::type operator*() { return *_ptr; }

		reference operator*() { return *_ptr; }

		pointer operator->() { return _ptr; }

		reference operator[](int index) { return _ptr[index]; }

		random_access_iterator &operator++() {
			_ptr++;
			return (*this);
		}

		random_access_iterator operator++(int) {
			random_access_iterator temp = *this;
			++(*this);
			return (temp);
		}

		random_access_iterator &operator--() {
			_ptr--;
			return (*this);
		}

		random_access_iterator operator--(int) {
			random_access_iterator temp = *this;
			--(*this);
			return (temp);
		}

		random_access_iterator &operator+=(int n) {
			this->_ptr += n;
			return (*this);
		}

		random_access_iterator &operator-=(unsigned int n) {
			this->_ptr -= n;
			return (*this);
		}

		random_access_iterator operator+(unsigned int n) const {
			random_access_iterator temp = *this;
			temp += n;
			return (temp);
		}

//		template<bool Q = Const>
//		typename ft::enable_if<Q, const random_access_iterator>::type operator+(unsigned int n) {
//			random_access_iterator temp = *this;
//			temp += n;
//			return (temp);
//		}

		random_access_iterator operator-(unsigned int n) {
			random_access_iterator temp = *this;
			temp -= n;
			return (temp);
		}

		friend difference_type operator-(random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr - rhs._ptr);
		}

		friend difference_type operator-(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr - rhs._ptr);
		}

		friend difference_type operator+(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr + rhs._ptr);
		}

		friend difference_type operator+(random_access_iterator &lhs, random_access_iterator &rhs) {
			return (lhs._ptr + rhs._ptr);
		}

		friend random_access_iterator operator+(int lhs, random_access_iterator rhs) {
			random_access_iterator temp = rhs;
			temp += lhs;
			return (temp);
		}

		friend bool operator>=(const random_access_iterator &a, const random_access_iterator &b) {
			return a._ptr >= b._ptr;
		}

		friend bool operator<=(const random_access_iterator &a, const random_access_iterator &b) {
			return a._ptr <= b._ptr;
		}

		friend bool operator<(const random_access_iterator &a, const random_access_iterator &b) {
			return a._ptr < b._ptr;
		}

		friend bool operator>(const random_access_iterator &a, const random_access_iterator &b) {
			return a._ptr > b._ptr;
		}

		friend bool operator==(const random_access_iterator &a, const random_access_iterator &b) {
			return a._ptr == b._ptr;
		}

		friend bool operator!=(const random_access_iterator &a, const random_access_iterator &b) {
			return a._ptr != b._ptr;
		}

		~random_access_iterator() {};
	};
}

#endif
