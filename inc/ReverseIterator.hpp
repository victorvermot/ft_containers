#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

# include "Iterator.hpp"
# include "RaIterator.hpp"
# include "IteratorTraits.hpp"

template <typename Iterator>
class reverse_iterator {

public:
	typedef Iterator iterator_type;
//	typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
//	typedef typename ft::iterator_traits<Iterator>::value_type value_type;
//	typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
//	typedef typename ft::iterator_traits<Iterator>::pointer pointer;
//	typedef typename ft::iterator_traits<Iterator>::reference reference;

	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;

private:

	Iterator current;

public:

	// Constructors
	reverse_iterator() : current() {};
	explicit reverse_iterator (const iterator_type& it) : current(it) {}
	template <class Iter>
	explicit reverse_iterator (const reverse_iterator<Iter>& rev_it) {
		this->current = rev_it.base();
	}

	operator reverse_iterator<ft::random_access_iterator<const value_type> >() const {
		return (reverse_iterator<ft::random_access_iterator<const value_type> >(this->base()));
	}

	// Member function
	iterator_type base() const { return current; }

	// Member function operator overloader
	reverse_iterator& operator++() {
		--current;
		return (*this);
	}
	reverse_iterator operator++(int) {
		reverse_iterator temp = *this;
		--current;
		return temp;
	}

	reverse_iterator& operator--() {
		++current;
		return (*this);
	}
	reverse_iterator operator--(int) {
		reverse_iterator temp = *this;
		++current;
		return (temp);
	}
	reference operator*() const {
		Iterator tmp = current;
		return *--tmp;
	}
	pointer operator->() const {
		return &(operator*());
	}
	reverse_iterator operator-(difference_type n) {
		return reverse_iterator(current + n);
	}
	reverse_iterator operator+(difference_type n) {
		return reverse_iterator(current - n);
	}
	const reverse_iterator operator+(difference_type n) const {
		return reverse_iterator(current - n);
	}
	reverse_iterator operator+=(difference_type n) {
		current -= n;
		return (*this);
	}
	reverse_iterator operator-=(difference_type n) {
		current += n;
		return (*this);
	}
	reference operator[](difference_type n) const {
		return *(*this + n);
	}

	// Non member function overloads
	friend bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}
	friend bool operator==(reverse_iterator<Iterator>& lhs, reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}
	friend bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return !(lhs.base() == rhs.base());
	}
	friend bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (rhs.base() < lhs.base());
	}
	friend bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return !(rhs < lhs);
	}
	friend bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (rhs < lhs);
	}
	friend bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return !(lhs < rhs);
	}
	friend reverse_iterator<Iterator> operator+(difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return (reverse_iterator(rev_it.current - n));
	}
	friend reverse_iterator<Iterator> operator+(difference_type n, reverse_iterator<Iterator>& rev_it) {
		return (reverse_iterator(rev_it.current - n));
	}
	friend difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (rhs.current - lhs.current);
	}
};


#endif
