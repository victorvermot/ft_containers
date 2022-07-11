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
		typedef ft::bidirectional_iterator<key_type> 			iterator;
//		typedef ft::random_access_iterator<const value_type>	const_iterator;
//		typedef reverse_iterator<const_iterator> 				const_reverse_iterator;
//		typedef reverse_iterator<iterator> 						reverse_iterator;

//		struct Node {
//			ft::pair<Key, T> data;
//			Node* left;
//			Node* right;
//		};

		class bstree {
		public:
			struct Node {
				ft::pair<key_type, mapped_type> data;
				Node* left;
				Node* right;
				Node* parent;
			};

			class bstIterator {

			private:

				const Node* 	nodePtr;
				const bstree*	tree;

			public:

				bool operator==(const bstIterator& rhs) const {
					return (tree == rhs.tree && nodePtr == rhs.nodePtr);
				}
				bool operator!=(const bstIterator& rhs) const {
					return !(*this == rhs);
				}
			};

			Node* insert(Node* root, ft::pair<key_type, mapped_type> data) {
				if (root == NULL) {
					root = getNewNode(data);
				}
				else if (Compare(data.first, root->data.first)) {
					root->left = insert(root->left, data);
				}
				else {
					root->right = insert(root->right, data);
				}
				return (root);
			}

			Node* minValueNode(Node* node) {
				Node* current = node;

				while (current && current->left != NULL)
					current = current->left;
				return current;
			}

			Node* deleteNode(Node* root, key_type key) {
				if (root == NULL)
					return root;
				if (Compare(key, root->data.first)) {
					root->left = deleteNode(root->left, key);
				}
				else if (!Compare(key, root->data.first)) {
					root->right = deleteNode(root->right, key);
				}
				else {
					if (root->left == NULL && root->right == NULL)
						return NULL;
					else if (root->left == NULL) {
						Node* temp = root->right;
						free(root);
						return temp;
					}
					else if (root->right == NULL) {
						Node* temp = root->left;
						free(root);
						return temp;
					}
					Node* temp = minValueNode(root->right);
					root->data = temp->data;
					root->right = deleteNode(root->right, temp->key);
				}
				return root;
			}

			Node* search(Node* root, key_type key) {
				if (root == NULL || root->key == key)
					return root;
				if (root->key < key)
					return search(root->right, key);
				return search(root->left, key);
			}

			Node* getNewNode(ft::pair<key_type, key_compare> data) {
				Node* newNode = new Node();
				newNode->data = data;
				newNode->left = NULL;
				newNode->right = NULL;
				return newNode;
			}
		};

	private:

		bstree		_tree;
		Alloc		_alloc;
		size_type	_size;

	public:
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_tree(), _size(), _alloc(alloc) {}

		map (const map& x) {}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) {}
		~map() {}

		bool empty() { return !_size; }
		size_type size() { return _size; }
		size_type max_size() { return _alloc.max_size(); }

		pair<iterator,bool> insert (const value_type& val) {

		}

		Alloc get_allocator() { return _alloc; }
	};
}

#endif
