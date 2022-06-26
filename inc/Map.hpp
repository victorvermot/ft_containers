#ifndef MAP_H
# define MAP_H
# include "Pair.hpp"
# include <memory>

// TODO Bidirect iterator
// TODO La fonction nested qui compare les values

namespace ft {

	template < class Key,
			class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key,T> >
	>
	class map {

	public:

		typedef Key 		key_type;
		typedef T 			mapped_type;
		typedef Compare 	key_compare;
//		typedef une fonction nested 	value_compare;
		typedef ft::pair<const key_type,mapped_type>	value_type;
		typedef Alloc 		allocator_type;
		typedef typename 	allocator_type::reference reference;
		typedef typename 	allocator_type::const_reference const_reference;
		typedef typename 	allocator_type::pointer pointer;
		typedef typename 	allocator_type::const_pointer const_pointer;
		typedef	size_t		size_type;
		typedef	std::ptrdiff_t 		difference_type;
//		typedef ft::random_access_iterator<value_type> 			iterator;
//		typedef ft::random_access_iterator<const value_type>	const_iterator;
//		typedef reverse_iterator<const_iterator> 				const_reverse_iterator;
//		typedef reverse_iterator<iterator> 						reverse_iterator;

		struct Node {
			ft::pair<Key, T> data;
			Node* left;
			Node* right;
		};

	private:

		Node* root;

	public:
		map(){}
	};
}

#endif
