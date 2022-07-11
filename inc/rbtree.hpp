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

	Node* insert(Node* root, ft::pair<T, U> data) {
		if (root == NULL) {
			root = getNewNode(data);
		}
		else if (data <= root->data) {
			root->left = insert(root->left, data);
		}
		else {
			root->right = insert(root->right, data);
		}
		return (root);
	}

	Node* deleteNode(Node* root, T key) {
		if (root == NULL)
			return root;
		if (std::less<T>(key, 5)) {

		}
	}

	Node* search(Node* root, T key) {
		if (root == NULL || root->key == key)
			return root;
		if (root->key < key)
			return search(root->right, key);
		return search(root->left, key);
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
