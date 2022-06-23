#ifndef VECTOR_H
# define VECTOR_H

# include "ReverseIterator.hpp"
# include "RaIterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include <iostream>
# include <memory>
# include <stdexcept>
# include "lexicographical_compare.hpp"

namespace ft {
	template <typename T, typename Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T 			value_type;
		typedef Alloc 		allocator_type;
		typedef typename 	allocator_type::reference reference;
		typedef typename 	allocator_type::const_reference const_reference;
		typedef typename 	allocator_type::pointer pointer;
		typedef typename 	allocator_type::const_pointer const_pointer;
		typedef	size_t		size_type;
		typedef ft::random_access_iterator<value_type> 			iterator;
		typedef ft::random_access_iterator<const value_type>	const_iterator;
		typedef reverse_iterator<const_iterator> 				const_reverse_iterator;
		typedef reverse_iterator<iterator> 						reverse_iterator;

	private:
		// private members
		value_type 			*_vector;
		allocator_type 		_alloc;
		size_type 			_size;
		size_type 			_capacity;

		void	ft_free() {
			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(_vector + i);
			}
			_alloc.deallocate(_vector, _capacity);
		}

	public:
		// Constructors and destructor
		explicit vector() : _size(0), _capacity(0) {
			_vector = _alloc.allocate(0);
		}
		explicit vector<T, Alloc>(size_t size, const value_type& val = value_type(),
				  const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(size), _capacity(size) {
			_vector = _alloc.allocate(_capacity + 1);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_vector + i, val);
			}
		}
		template <class InputIterator>
		vector(typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
				const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
			InputIterator it = first;
			size_type	  diff = 0;
			for (; it != last; it++) {
				diff++;
			}
			_size = diff;
			_capacity = diff;
			_vector = _alloc.allocate(_capacity);
			std::uninitialized_copy(first, last, _vector);
		}
		vector(const vector& other) {
			*this = other;
		}
		~vector<T, Alloc>() {
			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(_vector + i);
			}
			_alloc.deallocate(_vector, _capacity);
		}

		// Operators Overload
		vector& operator=(const vector& rhs) {
			if (this != &rhs) {
				_alloc = rhs._alloc;
				_size = rhs._size;
				_capacity = rhs._size;
				_vector = _alloc.allocate(_capacity);
				std::uninitialized_copy(rhs.begin(), rhs.end(), _vector);
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
			if (n > _capacity * 2)
				_capacity = n;
			else if (n > _capacity)
				_capacity *= 2;
			value_type *temp = _alloc.allocate(_capacity);
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(temp + i, *(_vector + i));
			}
			if (n > _size) {
				for (size_type i = _size; i < n; i++) {
					_alloc.construct(temp + i, val);
				}
			}
			_alloc.deallocate(_vector, _capacity);
			_vector = temp;
			_size = n;
		}
		void reserve (size_type n) {
			if (n > this->max_size())
				throw std::length_error("The size provided is too big");
			if (n > _capacity) {
				value_type *temp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++) {
					_alloc.construct(temp + i, *(_vector + i));
				}
				for (size_type i = 0; i < _size; i++) {
					_alloc.destroy(_vector + i);
				}
				_alloc.deallocate(_vector, _capacity);
				_vector = temp;
				_capacity = n;
			}
		}

		// Element Access
		reference at (size_type n) {
			if (n >= _size) {
				throw std::out_of_range("Index out of range");
			}
			return (_vector[n]);
		}
		const_reference at (size_type n) const {
			if (n >= _size) {
				throw std::out_of_range("Index out of range");
			}
			return (_vector[n]);
		}
		reference front() { return (_vector[0]); }
		const_reference front() const { return (_vector[0]); }
		reference back() { return (_vector[_size - 1]); }
		const_reference back() const { return (_vector[_size - 1]); }

		// Iterator
		iterator begin() { return (iterator(_vector)); }
		const_iterator begin() const { return (const_iterator(_vector)); }
		iterator end() { return (iterator(_vector + _size)); }
		const_iterator end() const { return (const_iterator(_vector + _size)); }

		// reverse iterator
		reverse_iterator rbegin() { return (reverse_iterator(iterator(_vector + _size))); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(const_iterator(_vector + _size))); }
		reverse_iterator rend() { return (reverse_iterator(iterator(_vector))); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(const_iterator(_vector))); }

		// Function members modifiers
		template <class InputIterator>
		void assign (typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
			InputIterator it1 = first;
			size_type	  diff = 0;
			for (; it1 != last; it1++) {
				diff++;
			}
			if (diff > _capacity) {
				this->reserve(diff);
			}
			int i = 0;
			for (InputIterator it = first; it != last; it++) {
				_alloc.construct(_vector + i, *it);
				i++;
			}
			_size = diff;
		}

		void assign(size_type n, const value_type& val) {
			if (n > _capacity) {
				this->reserve(n);
			}
			std::uninitialized_fill_n(_vector, n, val);
			_size = n;
		}

		void push_back(const value_type& val) {
			if (_capacity == 0)
				_capacity = 1;
			else if (_size + 1 > _capacity) {
				_capacity *= 2;
				this->reserve(_capacity);
			}
			_size++;
			this->back() = val;
		}

		void swap (vector& x) {
			size_type temp;
			temp = this->_size;
			this->_size = x._size;
			x._size = temp;

			temp = this->_capacity;
			this->_capacity = x._capacity;
			x._capacity = temp;
			std::swap(this->_vector, x._vector);
		}

		void pop_back() {
			_alloc.destroy(&this->back());
			_size--;
		}

		iterator insert(iterator position, const value_type& val) {
			size_type diff = position - this->begin();

			if (_size + 1 > _capacity) {
				_capacity *= 2;
				this->reserve(_capacity);
			}
			value_type *temp = _alloc.allocate(_capacity);
			_size++;
			std::uninitialized_copy(this->begin(), position, temp);
			temp[position - this->begin()] = val;
			std::uninitialized_copy(position, this->end(), temp + (position - this->begin() + 1));
			_vector = temp;
			return (iterator(_vector + diff));
		}

		void insert(iterator position, size_type n, const value_type& val) {
			if (_size + n > _capacity) {
				_capacity = _size + n;
				this->reserve(_capacity);
			}
			value_type *temp = _alloc.allocate(_capacity);
			std::uninitialized_copy(this->begin(), position, temp);
			std::uninitialized_fill_n(temp + (position - this->begin()), n, val);
			std::uninitialized_copy(position, this->end(), temp + (position - this->begin() + n));
			_alloc.deallocate(_vector, _capacity);
			_vector = temp;
			_size += n;
		}

		template <class InputIterator>
		void insert (iterator position, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
			InputIterator it1 = first;
			size_type	  diff = 0;
			for (; it1 != last; it1++) {
				diff++;
			}
			if (_size + diff > _capacity) {
				_capacity = _size + diff;
			}
			value_type *temp = _alloc.allocate(_capacity);
			std::uninitialized_copy(this->begin(), position, temp);
			std::uninitialized_copy(first, last, temp + (position - this->begin()));
			std::uninitialized_copy(position, this->end(), temp + (position - this->begin() + diff));
			_alloc.deallocate(_vector, _capacity);
			_vector = temp;
			_size += diff;
		}

		iterator erase(iterator position) {
			_size--;
			for (iterator it = position; it != this->end(); it++) {
				*it = *(it + 1);
			}
			return (position);
		}

		iterator erase(iterator first, iterator last) {
			size_type diff = last - first;
			for (iterator it = first; it != last + 1; it++) {
				*it = *(it + diff);
			}
			_size -= diff;
			return (first);
		}

		void clear() {
			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(_vector + i);
			}
			_size = 0;
		}

		friend bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs._size != rhs._size)
				return (lhs._size == rhs._size);
			else
			{
				for (size_type i = 0; i < lhs._size; i++) {
					if (lhs.at(i) != rhs.at(i))
						return false;
				}
			}
			return true;
		}
		friend bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs == rhs);
		}
		friend bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		friend bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return (rhs < lhs);
		}
		friend bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs < rhs);
		}
		friend bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(rhs < lhs);
		}
		friend void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
			size_type temp;
			temp = x._size;
			x._size = y._size;
			y._size = temp;

			temp = x._capacity;
			x._capacity = y._capacity;
			y._capacity = temp;
			std::swap(x._vector, y._vector);
		}

		// ALlocators
		allocator_type get_allocator() const { return (_alloc); }
	};
}

#endif
