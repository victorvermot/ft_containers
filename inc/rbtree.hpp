#ifndef RBTREE_HPP
# define RBTREE_HPP

#include "Pair.hpp"
#include <iostream>

#define RED 0
#define BLACK 1

template <typename T, typename U>
class rbtree {
public:
	struct Node {
		ft::pair<T, U> data;
		int	  color;
		Node* left;
		Node* right;
	};

	void insert(Node* root, ft::pair<T, U> data) {

	}
	Node* getNewNode(ft::pair<T, U> data) {
		Node* newNode = new Node();
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
};

#endif
