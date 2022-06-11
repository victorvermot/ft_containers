#ifndef VECTOR_H
# define VECTOR_H

# include "ReverseIterator.hpp"
# include "RaIterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include <iostream>
# include <memory>
# include <stdexcept>

namespace ft {
	template <typename T, typename Alloc = std::allocator<T> >
	class vector {

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
		vector<T, Alloc>() : _size(0), _capacity(0) {
			_vector = _alloc.allocate(_capacity);
		}
		vector<T, Alloc>(size_t size, const value_type& val) : _size(size), _capacity(size) {
			_vector = _alloc.allocate(_capacity + 1);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_vector + i, val);
			}
//			std::uninitialized_fill_n(_vector, size, val);
		}
		vector<T, Alloc>(const vector& other) {
			*this = other;
		}
		~vector<T, Alloc>() {
			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(_vector + i);
			}
//			_alloc.deallocate(_vector, _capacity);
		}

		// Operators Overload
		vector& operator=(const vector& rhs) {
			if (this != &rhs) {
				_alloc = rhs._alloc;
				_size = rhs._size;
				_vector = _alloc.allocate(rhs._capacity);
				for (size_t i = 0; i < _size - 1; i++) {
					_alloc.construct(_vector + i, *(rhs._vector + i));
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
			if (n > _capacity)
				_capacity = n;
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
		reference back() { return (_vector[_size]); }
		const_reference back() const { return (_vector[_size]); }

		// Iterator
		iterator begin() { return (iterator(this->front())); }
		const_iterator begin() const { return (const_iterator(this->front())); }
		iterator end() { return (iterator(this->back())); }
//		typename enable_if<!is_integral<InputIterator>::value>::type
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			if (static_cast<long unsigned int>(last - first) > _capacity) {
				this->reserve(last - first);
			}
			int i = 0;
			for (InputIterator it = first; it != last; it++) {
				_alloc.construct(_vector + i, *it);
				i++;
			}
			_size = last - first;
		}
		void assign(size_type n, const value_type& val) {
			if (n > _capacity) {
				this->reserve(n);
			}
			std::uninitialized_fill_n(_vector, n, val);
			_size = n;
		}
		// Modifiers
		void push_back(const value_type& val) {
			if (_size + 1 > _capacity) {
				_capacity *= 2;
				this->reserve(_capacity);
			}
			this->back() = val;
			_size++;
		}
		void swap (vector& x) {
//			vector& tmp = *this;
//			*this = x;
//			x = tmp;
//			iterator it2 = x.begin();
			std::swap(this->_vector, x._vector);
//			  std::uninitialized_fill_n(_vector, n, val);
//			std::uninitialized_copy(this->begin(), this->end(), x._vector);
//			std::uninitialized_copy(this->begin(), this->end(), x._vector);
//			std::uninitialized_copy(this->begin(), this->end(), this->_vector);
//			for (iterator it = this->begin(); it != this->end(); it++) {
//				T temp = *it;
//				*it = *it2;
//				*it2 = temp;
//				it2++;
//			}
		}
		void pop_back() {
			_alloc.destroy(&this->back());
			_size--;
		}
		iterator insert(iterator position, const value_type& val) {
			if (_size + 1 > _capacity) {
				_capacity *= 2;
				this->reserve(_capacity);
			}
			value_type temp = *position;
			*position = val;
			*(position + 1) = temp;
			if (position + 2 != this->end()) {
				for (iterator it = position + 2; it != this->end(); it++) {
					*it = *(it - 1);
				}
			}
			_size++;
			return (position);
		}
		void insert(iterator position, size_type n, const value_type& val) {
			if (_size + n > _capacity) {
				_capacity = _size + n;
				this->reserve(_capacity);
			}
//			value_type *new_vector = _alloc.allocate(_capacity);
			value_type *temp = _alloc.allocate(_capacity);
//			new_vector
//			int j = 0;
//			std::uninitialized_copy<ft::vector<value_type>, value_type* >(this->begin(), position, temp);
			std::uninitialized_copy(this->begin(), position, temp);
//			std::uninitialized_copy<ft::vector<value_type>, value_type* >(position, position + n, temp + position);
			std::uninitialized_fill_n(temp + (position - this->begin()), n, val);
			std::uninitialized_copy(position, position + n, temp + (position - this->begin() + n));
//			std::cout << "El famoso: "<< temp + (position - this->begin() + n) << std::endl;
			_alloc.deallocate(_vector, _capacity);
			_vector = temp;
			_size += n;
		}
		iterator erase (iterator position) {
			for (iterator it = position; it != this->end() - 1; it++) {
				*it = *(it + 1);
			}
			_size--;
			return (position);
		}
		iterator erase(iterator first, iterator last) {
			size_type diff = last - first;
			for (iterator it = first; it != last; it++) {
				*it = *(it + diff);
			}
			_size -= diff;
			return (first);
		}
//		template <class InputIterator>
//		void insert (iterator position, InputIterator first, InputIterator last) {
//
//		}
		void clear() {
			_alloc.destroy(_vector);
			_size = 0;
		}

		friend bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs == rhs ); }
		friend bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs != rhs ); }
		friend bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs > rhs ); }
		friend bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs >= rhs ); }
		friend bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs < rhs ); }
		friend bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs <= rhs ); }
		friend void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
			iterator it2 = y.begin();
			for (iterator it = x.begin(); it != x.end(); it++) {
				T temp = *it;
				*it = y;
				*it2 = temp;
				it2++;
			}
		}

		// ALlocators
		allocator_type get_allocator() const { return (_alloc); }
	};
}

#endif
