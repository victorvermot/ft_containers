#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

# include "Iterator.hpp"
# include "RaIterator.hpp"
# include "IteratorTraits.hpp"

template <typename Iterator>
class reverse_iterator  : public ft::iterator<ft::random_access_iterator_tag, typename Iterator::value_type> {

public:
	typedef Iterator iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;

private:

	Iterator current;

public:

	// Constructors
	reverse_iterator() : current() {};
	explicit reverse_iterator (iterator_type it) { current = it; }
	template <class Iter>
	explicit reverse_iterator (const reverse_iterator<Iter>& rev_it) {
		this->current = rev_it._base();
		return (*this);
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
		return (temp);
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
		return *(--tmp);
	}
	pointer operator->() const {
		return &(operator*());
	}
	reverse_iterator operator+(difference_type n) {
		return reverse_iterator(current - n);
	}
	reverse_iterator operator+=(difference_type n) {
		current -= n;
		return (*this);
	}
	reverse_iterator operator-(difference_type n) {
		return reverse_iterator(current + n);
	}
	reverse_iterator operator-=(difference_type n) {
		current += n;
		return (*this);
	}
	reference operator[](difference_type n) const {
		return *(*(this + n));
	}

	// Non member function overloads
	friend bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}
	friend bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}
	friend bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}
	friend bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}
	friend bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}
	friend bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}
	friend reverse_iterator<Iterator> operator+(difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return (reverse_iterator(rev_it - n));
	}
	friend reverse_iterator<Iterator> operator-(difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return (reverse_iterator(rev_it + n));
	}
};


#endif
