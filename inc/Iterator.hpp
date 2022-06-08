#ifndef ITERATOR_H
# define ITERATOR_H

template <class Category, class T, class Distance = std::ptrdiff_t,
		class Pointer = T*, class Reference = T&>
struct iterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

#endif
