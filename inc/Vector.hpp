#ifndef VECTOR_H
# define VECTOR_H

# include "ReverseIterator.hpp"
# include "RaIterator.hpp"
# include <iostream>
# include <memory>
# include <stdexcept>

namespace ft {
	template <typename T, typename Alloc = std::allocator<T> >
	class Vector {

	private:
		typedef T 			value_type;
		typedef Alloc 		allocator_type;
		typedef typename 	allocator_type::reference reference;
		typedef typename 	allocator_type::const_reference const_reference;
		typedef typename 	allocator_type::pointer pointer;
		typedef typename 	allocator_type::const_pointer const_pointer;
		typedef	size_t		size_type;
		// private members
		value_type 			*_vector;
		allocator_type 		_alloc;
		size_type 			_size;
		size_type 			_capacity;

	public:
		typedef RaIterator<value_type> 			iterator;
		typedef RaIterator<const value_type> 	const_iterator;
		typedef ReverseIterator<iterator> 		reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;

		// Constructors and destructor
		Vector<T, Alloc>() : _size(0), _capacity(0) {
			_vector = _alloc.allocate(_size);
		}
		Vector<T, Alloc>(size_t size, const value_type& val) : _size(size), _capacity(size) {
			_vector = _alloc.allocate(_size);
			std::uninitialized_fill_n(_vector, size, val);
		}
		Vector<T, Alloc>(const Vector& other) {
			*this = other;
		}
		~Vector<T, Alloc>() {
			_alloc.deallocate(_vector, _size);
		}

		// Operators Overload
		Vector& operator=(const Vector& rhs) {
			if (this != &rhs) {
				_alloc = rhs._alloc;
				_size = rhs._size;
				_vector = _alloc.allocate(_size);
//				std::uninitialized_copy_n()
				for (size_t i = 0; i < _size; i++) {
					_vector[i] = rhs._vector[i];
				}
			}
			return (*this);
		}
		reference operator[](size_type index)
		{
			return (_vector[index]);
		}

		// Capacity functions
		size_type size() const { return (_size); }
		bool empty() const { return (_size == 0); }
		size_type max_size() const { return (_alloc.max_size()); }
		size_type capacity() const { return (_capacity); }
		void resize (size_type n, value_type val = value_type()) {
			// TODO ca segfault for some reason si on rentre dans cette condition
			if (n < _size)
				_alloc.deallocate(_vector + n, _size - n);
			else {
				_alloc.deallocate(_vector, _size);
				_vector = _alloc.allocate(n);
			}
			_vector = std::uninitialized_fill_n(_vector, n, val);
			_size = n;
		}
		void reserve (size_type n) {
			// TODO Throw une exception si n est plus grand que la size max
			if (n > this->max_size())
				throw std::length_error("The size provided is too big");
			if (n > _size) {
				_vector = _alloc.allocate(n);
			}
		}

		// Element Access
		reference at (size_type n) {
			if (n > _size) {
				throw std::out_of_range("Index out of range");
			}
			return (_vector[n]);
		}
		const_reference at (size_type n) const {
			if (n > _size) {
				throw std::out_of_range("Index out of range");
			}
			return (_vector[n]);
		}
		reference front() { return (_vector[0]); }
		const_reference front() const { return (_vector[0]); }
		reference back() { return (_vector[_size - 1]); }
		const_reference back() const { return (_vector[_size - 1]); }

		// Iterator
		iterator begin() { return (iterator(_vector[0])); }
		const_iterator begin() const { return (const_iterator(_vector[0])); }
		iterator end() { return (iterator(_vector[_size])); }

		// Modifiers
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			for (iterator it = first; it != last; it++) {
				*it = 0;
			}
		}
		void assign (size_type n, const value_type& val) {
			if (n > _capacity) {
				_alloc.allocate(n);
			}
			_vector = std::uninitialized_fill_n(_vector, n, val);
		}
		void swap (Vector& x) {
			iterator it2 = x.begin();
			for (iterator it = this->begin(); it != this->end(); it++) {
				T temp = *it;
				*it = *it2;
				*it2 = temp;
				it2++;
			}
		}

		friend bool operator==(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) { return ( lhs == rhs ); }
		friend bool operator!=(const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) { return ( lhs != rhs ); }
		friend bool operator> (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) { return ( lhs > rhs ); }
		friend bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) { return ( lhs >= rhs ); }
		friend bool operator< (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) { return ( lhs < rhs ); }
		friend bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs) { return ( lhs <= rhs ); }
		friend void swap (Vector<T,Alloc>& x, Vector<T,Alloc>& y) {
			iterator it2 = y.begin();
			for (iterator it = x.begin(); it != x.end(); it++) {
				T temp = *it;
				*it = y;
				*it2 = temp;
				it2++;
			}
		}
	};
}

#endif
