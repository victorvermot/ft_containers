#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

template <typename Iterator>
class ReverseIterator {

private:
//	T *_ptr;
	typedef Iterator iterator_type;

public:
	ReverseIterator<iterator_type>() {};
//	ReverseIterator<iterator_type>(T *ptr) : _ptr(ptr) { return ; }
//	T& operator*() const { return *_ptr; }
//	T* operator->() const { return _ptr; }
	ReverseIterator& operator++() {
//		_ptr++;
		return (*this);
	}
	ReverseIterator& operator++(int) {
		ReverseIterator temp = *this;
		++(*this);
		return (temp);
	}
	friend bool operator== (const ReverseIterator& a, const ReverseIterator& b) { return a.m_ptr == b.m_ptr; }
	friend bool operator!= (const ReverseIterator& a, const ReverseIterator& b) { return a.m_ptr != b.m_ptr; }
//	~ReverseIterator<T>() { return ; };
};


#endif
