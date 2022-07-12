#ifndef MAP_H
# define MAP_H
# include "Pair.hpp"
# include <memory>
# include <functional>

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
		typedef ft::pair<key_type, mapped_type>	value_type;
		typedef Alloc 		allocator_type;
		typedef typename 	allocator_type::reference reference;
		typedef typename 	allocator_type::const_reference const_reference;
		typedef typename 	allocator_type::pointer pointer;
		typedef typename 	allocator_type::const_pointer const_pointer;
		typedef	size_t		size_type;
		typedef	std::ptrdiff_t 		difference_type;
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
		protected:
			Compare comp;
		public:
			explicit value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};
		class bstree {
		public:
			struct Node {
				ft::pair<key_type, mapped_type> data;
				Node* left;
				Node* right;
				Node* parent;
				Node(const value_type& newdata, Node* lt, Node* rt, Node* par) :
					data(newdata), left(lt), right(rt), parent (par) { }
			};

		private:

			map _my_map;
			Node* root;

			Node* insert(Node* root, Node* par, const value_type& data) {
				if (root == NULL) {
					root = new Node(data, NULL, NULL, par);
					return root;
				}
				else if (_my_map._ftCompare(data.first, root->data.first)) {
					root->left = insert(root->left, par, data);
				}
				else if (!value_compare(data.first, root->data.first)) {
					root->right = insert(root->right, par, data);
				}
				return (root);
			}

		public:

			class bstIterator {

			private:
				friend class bstree;
				// NodePtr is the current location in the tree
				const Node* 	nodePtr;
				const bstree*	tree;

			public:
				typedef ft::pair<key_type, mapped_type> value_type;

				bstIterator(const Node* p, const bstree* t) : nodePtr(p), tree(t) {}
				bstIterator() : nodePtr(NULL), tree(NULL) {}
				bstIterator(const bstIterator& other) {
					*this = other;
				}
				~bstIterator() {}

				bstIterator& operator=(const bstIterator& rhs) {
					if (this != &rhs) {
						nodePtr = rhs.nodePtr;
						tree = rhs.tree;
					}
					return *this;
				}

				bool operator==(const bstIterator& rhs) const {
					return (tree == rhs.tree && nodePtr == rhs.nodePtr);
				}
				bool operator!=(const bstIterator& rhs) const {
					return !(*this == rhs);
				}
				value_type operator->() const {
					if (nodePtr)
						return nodePtr->data;
				}
				value_type& operator*() const {
					if (nodePtr)
						return nodePtr->data;
				}
				bstIterator& operator++() {
					Node* p;
					if (nodePtr == NULL) {
						nodePtr = tree->root;
						if (nodePtr == NULL) {
							throw std::exception();
						}
						while (nodePtr->left != NULL) {
							nodePtr = nodePtr->left;
						}
					}
					else {
						if (nodePtr->right != NULL) {
							while (nodePtr->right != NULL) {
								nodePtr = nodePtr->right;
							}
						}
						else {
							p = nodePtr->parent;
							while (p != NULL && nodePtr == p->right) {
								nodePtr = p;
								p = p->parent;
							}
							nodePtr = p;
						}
					}
					return *this;
				}
				bstIterator operator++(int) {
					bstIterator temp = *this;
					operator++();
					return temp;
				}
				bstIterator& operator--() {
					Node* p;

					if (nodePtr == NULL) {
						nodePtr = tree->root;
						if (nodePtr == NULL)
							throw std::exception();
						while (nodePtr->right != NULL)
							nodePtr = nodePtr->right;
					}
					else if (nodePtr->right != NULL) {
						nodePtr = nodePtr->left;
						while (nodePtr->right != NULL)
							nodePtr = nodePtr->right;
					}
					else {
						p = nodePtr->parent;
						while (p != NULL && nodePtr == p->left) {
							nodePtr = p;
							p = p->parent;
						}
						nodePtr = p;
					}
					return *this;
				}
				bstIterator operator--(int) {
					bstIterator temp = *this;
					operator--();
					return temp;
				}
			};

			typedef bstIterator const_iterator;
			typedef const_iterator iterator;

			bstree() : root(NULL), _my_map() {}

			const_iterator insert(const value_type& x) {
				Node* temp = insert(root, NULL, x);
				if (temp == NULL)
					return end();
				else
					return const_iterator(temp, this);
			}

			Node* minValueNode(Node* node) {
				Node* current = node;

				while (current && current->left != NULL)
					current = current->left;
				return current;
			}

			Node* maxValueNode(Node* node) {
				Node* current = node;

				while (current && current->right != NULL)
					current = current->right;
				return current;
			}

			void makeEmpty(Node* root) {
				if (root) {
					makeEmpty(root->left);
					makeEmpty(root->right);
					delete root;
				}
				root = NULL;
			}

			Node* deleteNode(Node* root, key_type key) {
				if (root == NULL)
					return root;
				if (_my_map._ftCompare(key, root->data.first)) {
					root->left = deleteNode(root->left, key);
				}
				else if (!_my_map._ftCompare(key, root->data.first)) {
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

			const_iterator begin() {
				return bstIterator(minValueNode(root), this);
			}

			const_iterator end() {
				return bstIterator(minValueNode(NULL), this);
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

		value_compare _ftCompare;
		typedef typename bstree::bstIterator const_iterator;
		typedef const_iterator iterator;

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_tree(), _size(), _alloc(alloc), _ftCompare(comp) {}

		map (const map& x) {}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) {}
		~map() {}

		const_iterator begin() {
			return _tree.begin();
		}
		const_iterator end() {
			return _tree.end();
		}

		bool empty() { return !_size; }
		size_type size() { return _size; }
		size_type max_size() { return _alloc.max_size(); }

		pair<iterator,bool> insert (const value_type& val) {
			return (ft::make_pair<iterator, bool>(_tree.insert(val), true));
		}

		Alloc get_allocator() { return _alloc; }
	};
}

#endif
