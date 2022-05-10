#ifndef VECTOR_H
# define VECTOR_H

# include <iostream>

namespace ft {
	template <typename T>
	class Vector {
	public:
		Vector<T>(){
			_vector = _alloc.allocate(0);
			return ;
		}
		Vector<T>(size_t size) : _size(size) {
			_vector = _alloc.allocate(_size);
			return ;
		}
		Vector<T>(const Vector& other) {
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
		~Vector<T>(){
			_alloc.deallocate(_vector, _size);
			return ;
		}

		size_t	size() { return (_size); }

	private:
		size_t				_size;
		T					*_vector;
		std::allocator<T>	_alloc;
	};
}

#endif
