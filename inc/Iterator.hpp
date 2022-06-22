#ifndef ITERATOR_H
# define ITERATOR_H

#include "iostream"

namespace ft {
	template <class Category, typename T>
	class iterator {
	public:
		typedef T         value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T*   	pointer;
		typedef T& 		reference;
		typedef Category  iterator_category;
	};
}

#endif
