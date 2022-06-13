#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

# include "Iterator.hpp"

template <typename Iterator>
class reverse_iterator  : public ft::iterator<> {

private:
//	T *_ptr;
//	typedef T value_type;
//	typedef T& reference;
//	typedef T* pointer;
//	typedef std::random_access_iterator_tag iterator_category;
//	typedef std::ptrdiff_t difference_type;

public:
//	reverse_iterator<iterator_type>() {};
//	reverse_iterator<iterator_type>(T *ptr) : _ptr(ptr) { return ; }
//	T& operator*() const { return *_ptr; }
//	T* operator->() const { return _ptr; }
	reverse_iterator& operator++() {
//		_ptr++;
		return (*this);
	}
	reverse_iterator& operator++(int) {
		reverse_iterator temp = *this;
		++(*this);
		return (temp);
	}
	friend bool operator== (const reverse_iterator& a, const reverse_iterator& b) { return a.m_ptr == b.m_ptr; }
	friend bool operator!= (const reverse_iterator& a, const reverse_iterator& b) { return a.m_ptr != b.m_ptr; }
//	~reverse_iterator<T>() { return ; };
};


#endif
