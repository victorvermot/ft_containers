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
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Alloc 		allocator_type;
		typedef typename 	allocator_type::reference reference;
		typedef typename 	allocator_type::const_reference const_reference;
		typedef typename 	allocator_type::pointer pointer;
		typedef typename 	allocator_type::const_pointer const_pointer;
		typedef	size_t		size_type;
		typedef	std::ptrdiff_t 		difference_type;

		class bstree {
		public:
			struct Node {
				value_type data;
				Node* left;
				Node* right;
				Node* parent;
				Node(const value_type& newdata, Node* lt, Node* rt, Node* par) :
					data(newdata), left(lt), right(rt), parent (par) { }
			};

		private:

			Node* _root;
			Alloc _alloc;

			Node* insert(Node*& r, Node* par, const value_type& data) {
				if (r == NULL) {
					r = new Node(data, NULL, NULL, par);
					return r;
				}
				else if (Compare()(data.first, r->data.first)) {
					return insert(r->left, r, data);
				}
				else if (Compare()(r->data.first, data.first)) {
					return insert(r->right, r, data);
				}
                else
                    return r;
			}

            void makeEmpty(Node*& r) {
                if (r) {
                    makeEmpty(r->left);
                    makeEmpty(r->right);
                    delete r;
                }
                r = NULL;
            }

		public:

			class bstIterator {

			private:
				friend class bstree;
				// NodePtr is the current location in the tree
				Node* 	nodePtr;
				const bstree*	tree;

			public:
				typedef ft::pair<const key_type, mapped_type> value_type;

				bstIterator(Node* p, const bstree* t) : nodePtr(p), tree(t) {}
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
					return (tree != rhs.tree || nodePtr != rhs.nodePtr);
				}
				pointer operator->() const {
					if (nodePtr == NULL)
						throw std::exception();
					return &(nodePtr->data);
				}
				reference operator*() const {
					if (nodePtr == NULL)
						throw std::exception();
					return nodePtr->data;
				}
				bstIterator& operator++() {
					Node* p;
					if (nodePtr == NULL) {
						nodePtr = tree->_root;
						if (nodePtr == NULL) {
							throw std::exception();
						}
						while (nodePtr->left != NULL) {
							nodePtr = nodePtr->left;
						}
					}
					else {
						if (nodePtr->right != NULL) {
                            nodePtr = nodePtr->right;
							while (nodePtr->left != NULL) {
								nodePtr = nodePtr->left;
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
						nodePtr = tree->_root;
						if (nodePtr == NULL)
							throw std::exception();
						while (nodePtr->right != NULL)
							nodePtr = nodePtr->right;
					}
					else if (nodePtr->left != NULL) {
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

			bstree() : _root(NULL) {}

            bstree(const bstree& other) : _root(NULL) {
                *this = other;
            }

            void setParent(Node *r) {
                if (r)
                {
                    if (r->left != NULL) {
                        r->left->parent = r;
                        setParent(r->left);
                    }
                    if (r->right != NULL) {
                        r->right->parent = r;
                        setParent(r->right);
                    }
                }
            }

            bstree& operator=(const bstree& rhs) {
                if (this != &rhs) {
                    _root = clone(rhs._root);
//                    setParent(_root);
//                    _root->parent = NULL;
                }
                return *this;
            }

            Node* clone(Node* r) const {
                if (r == NULL)
                    return NULL;
                else
                    return new Node(r->data, clone(r->left), clone(r->right), r->parent);
            }

			const_iterator insert(const value_type& x) {
				Node* temp = insert(_root, NULL, x);
//                setParent(_root);
//                _root->parent = NULL;
				if (temp == NULL)
					return end();
				else
				    return const_iterator(temp, this);
			}

//			const_iterator insert(value_type x) {
//				Node* temp = insert(&_root, NULL, x);
//				if (temp == NULL)
//					return end();
//				else
//					return const_iterator(temp, this);
//			}


			Node* minValueNode(Node* node) const {
				if (node == NULL)
                    return NULL;
                if (node->left == NULL)
                    return node;
                return minValueNode(node->left);
			}

            Node** getRoot() {
                return &_root;
            }

			Node* maxValueNode(Node* node) const {
				Node* current = node;

				while (current && current->right != NULL)
					current = current->right;
				return current;
			}

            void makeEmpty() {
                makeEmpty(_root);
            }

            bool deleteNode(iterator position) {
                bool ret = deleteNode(_root, (*position).first);
                if (ret) {
//                    setParent(_root);
                    return true;
                }
            }

            bool deleteNode(const key_type& k) {
                bool ret = deleteNode(_root, k);
                if (ret) {
//                    setParent(_root);
                    return true;
                }
                return false;
            }

			bool deleteNode(Node*& r, key_type key) {
				if (r == NULL)
					return false;
				if (Compare()(key, r->data.first)) {
					return deleteNode(r->left, key);
				}
				else if (Compare()(r->data.first, key)) {
					return deleteNode(r->right, key);
				}
				else if (r->left != NULL && r->right != NULL) {
                    r->data = minValueNode(r->right)->data;
                    deleteNode(r->right, r->data.first);
                    return true;
                }
                else {
					Node* temp = r;
                    r = (r->left != NULL) ? r->left : r->right;
                    if (r)
                        r->parent = temp->parent;
                    delete temp;
                    return true;
				}
			}

			const_iterator begin() const {
				return bstIterator(minValueNode(_root), this);
			}

			const_iterator find(const key_type& item) const {
				Node* t = _root;
				while (t != NULL && !(t->data.first == item)) {
					if (Compare()(item, t->data.first))
						t = t->left;
					else
						t = t->right;
				}
				return bstIterator(t, this);
			}

			const_iterator end() const {
				return bstIterator(NULL, this);
			}

			Node* search(Node* root, key_type key) {
				if (root == NULL || root->key == key)
					return root;
				if (root->key < key)
					return search(root->right, key);
				return search(root->left, key);
			}
//
//			Node* getNewNode(value_type data) {
//				Node* newNode = _alloc.allocate(sizeof(Node));
//				newNode->data = data;
//				newNode->left = NULL;
//				newNode->right = NULL;
//				return newNode;
//			}
		};

	private:

		key_compare _key_comp;
		Alloc		_alloc;
		bstree		_tree;
		size_type	_size;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
		protected:
			Compare comp;
		public:
			value_compare() {};
			explicit value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		value_compare _value_comp;

	public:

		typedef typename bstree::bstIterator const_iterator;
		typedef const_iterator iterator;

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			_key_comp(comp), _alloc(alloc), _tree(), _size(), _value_comp(comp) {}

		map (const map& x) {
			*this = x;
		}

		map& operator= (const map& rhs) {
			if (this != &rhs) {
				_alloc = rhs._alloc;
				_size = rhs._size;
				_key_comp = rhs._key_comp;
				_value_comp = rhs._value_comp;
				_tree = rhs._tree;
			}
			return *this;
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) : _key_comp(comp), _alloc(alloc), _size(0) {
			insert(first, last);
		}
		~map() {}

		const_iterator begin() const {
			return _tree.begin();
		}

		const_iterator end() const {
			return _tree.end();
		}

		bool empty() const { return !_size; }
		size_type size() const { return _size; }
		size_type max_size() const { return _alloc.max_size(); }

        pair<iterator, bool> insert(const value_type& val) {
			iterator temp = _tree.insert(val);
			if (temp == _tree.end())
				return (ft::make_pair<iterator, bool>(temp, false));
			_size++;
			return (ft::make_pair<iterator, bool>(temp, true));
		}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			InputIterator it = first;
			for (; it != last; it++) {
                _tree.insert(*it);
				_size++;
			}
		}

		iterator insert(iterator position, const value_type& val) {
			(void)position;
			iterator temp = _tree.insert(val);
			if (temp == _tree.end())
				return temp;
			_size++;
			return (ft::make_pair<iterator, bool>(temp, true));
		}

		Alloc get_allocator() { return _alloc; }

		// Operator overloads
		mapped_type& operator[] (const key_type& k) {
            const value_type test = ft::make_pair(k, T());
            pair<iterator, bool> ret = insert(test);
            if (ret.second)
                return ret.first->second;
		}

		void erase(iterator position) {
			_tree.deleteNode(position);
			_size--;
		}

		size_type erase(const key_type& k) {
            if (_tree.deleteNode(k)) {
			    _size--;
                return (1);
            }
            return (0);
		}

		void erase(iterator first, iterator last) {
            iterator temp = first;
            int i = 0;
            for (; temp != last; temp++) {
                i++;
            }
			for (; i > 0; i--) {
				_tree.deleteNode(first++);
				_size--;
			}
		}

		void swap(map& x) {
			std::swap(*this, x);
		}

		void clear() {
			_tree.makeEmpty();
			_size = 0;
		}

		key_compare key_comp() const {
			return _key_comp;
		}

		value_compare value_comp() const {
			return _value_comp;
		}

		iterator find(const key_type& k) {
			return _tree.find(k);
		}

		const_iterator find(const key_type& k) const {
			return _tree.find(k);
		}

		size_type count(const key_type& k) const {
			if (_tree.find(k) != _tree.end())
				return 1;
			else
				return 0;
		}
	};
}

#endif
