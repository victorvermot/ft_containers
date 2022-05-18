#ifndef VECTOR_H
# define VECTOR_H

# include "ReverseIterator.hpp"
# include "RaIterator.hpp"
# include <iostream>

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
		value_type 			*_vector;
		allocator_type 		_alloc;
		size_type 			_size;

	public:
		typedef RaIterator<value_type> iterator;
		typedef RaIterator<const value_type> const_iterator;
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;
		Vector<T, Alloc>() : _size(0) {
			_vector = _alloc.allocate(0);
		}
		Vector<T, Alloc>(size_t size, const value_type& val) : _size(size) {
			_vector = _alloc.allocate(_size);
			for (size_t i = 0; i < size; i++)
				_vector[i] = val;
		}
		Vector<T, Alloc>(const Vector& other) {
			*this = other;
		}
		Vector& operator=(const Vector& rhs) {
			if (this != &rhs) {
				_alloc = rhs._alloc;
				_size = rhs._size;
				_vector = _alloc.allocate(_size);
				for (size_t i = 0; i < _size; i++) {
					_vector[i] = rhs._vector[i];
				}
			}
			return (*this);
		}
		value_type& operator[](size_type index)
		{
			return (_vector[index]);
		}
		~Vector<T, Alloc>() {
			_alloc.deallocate(_vector, _size);
		}

		size_t	size() { return (_size); }
		iterator begin() { return (iterator(_vector[0])); }
		iterator end() { return (iterator(_vector[_size - 1])); }

	};
}

#endif
