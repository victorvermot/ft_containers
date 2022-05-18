#ifndef ITERATORTRAITS_H
# define ITERATORTRAITS_H

template <class Iterator>
class IteratorTraits {
public:
	IteratorTraits();

	IteratorTraits(const IteratorTraits &other);

	IteratorTraits &operator=(const IteratorTraits &rhs);

	~IteratorTraits();
private:
	typedef Iterator::difference_type
};


#endif
