#ifndef MAP_H
# define MAP_H
# include "Pair.hpp"
# include <memory>
# include <functional>
# include "ReverseIterator.hpp"
# include "lexicographical_compare.hpp"

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

			Node* insert(Node*& r, Node* par, const value_type& data, int& isNew) {
				if (r == NULL) {
                    r = _alloc.allocate(sizeof(Node));
                    _alloc.construct(r, Node(data, NULL, NULL, par));
//					r = new Node(data, NULL, NULL, par);
                    isNew = 1;
					return r;
				}
				else if (Compare()(data.first, r->data.first)) {
					return insert(r->left, r, data, isNew);
				}
				else if (Compare()(r->data.first, data.first)) {
					return insert(r->right, r, data, isNew);
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
            template <typename U>
			class bstIterator {

                class bstIteratorTag {};

			private:
				friend class bstree;
				// NodePtr is the current location in the tree
				Node* 	nodePtr;
				const bstree*	tree;

			public:

				typedef U value_type;
                typedef std::ptrdiff_t difference_type;
                typedef U* pointer;
                typedef U& reference;
                typedef bstIteratorTag iterator_category;

				bstIterator(Node* p, const bstree* t) : nodePtr(p), tree(t) {}
				bstIterator() : nodePtr(NULL), tree(NULL) {}
				bstIterator(const bstIterator& other) {
					*this = other;
				}
				~bstIterator() {}

                operator bstIterator<const U>() const {
                    return (bstIterator<const U>(this->nodePtr, this->tree));
                }

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

                void swap_data(Node* rhs) {
                    nodePtr->data = rhs->data;
                    nodePtr->right = rhs->right;
                    nodePtr->left = rhs->left;
                    nodePtr->parent = rhs->parent;
                }
			};

			typedef bstIterator<const value_type> const_iterator;
			typedef bstIterator<value_type> iterator;

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
                    setParent(_root);
                }
                return *this;
            }

            Node* clone(Node* r) const {
                if (r == NULL)
                    return NULL;
                else
                    return new Node(r->data, clone(r->left), clone(r->right), r->parent);
            }

			iterator insert(const value_type& x, int& isNew) {
				Node* temp = insert(_root, NULL, x, isNew);
                setParent(_root);
                return iterator(temp, this);
			}

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
                    return true;
                }
                return false;
            }

            bool deleteNode(const key_type& k) {
                bool ret = deleteNode(_root, k);
                if (ret) {
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
                    Node* test = maxValueNode(r->left);
                    Node* temp = r;
                    r = new Node(test->data, r->left, r->right, r->parent);
                    delete temp;
                    setParent(r);
                    deleteNode(r->left, r->data.first);
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

            iterator begin() {
                return iterator(minValueNode(_root), this);
            }

			const_iterator begin() const {
				return const_iterator(minValueNode(_root), this);
			}


			const_iterator find(const key_type& item) const {
				Node* t = _root;
				while (t != NULL && !(t->data.first == item)) {
					if (Compare()(item, t->data.first))
						t = t->left;
					else
						t = t->right;
				}
				return const_iterator(t, this);
			}

            iterator find(const key_type& item) {
                Node* t = _root;
                while (t != NULL && !(t->data.first == item)) {
                    if (Compare()(item, t->data.first))
                        t = t->left;
                    else
                        t = t->right;
                }
                return iterator(t, this);
            }

            const_iterator lower_bound(const key_type& item) const {
                Node* t = _root;

                while (t != NULL) {
                    if (t->data.first == item)
                        return (const_iterator(t, this));
                    else if (Compare()(item, t->data.first))
                        return (const_iterator(t, this));
                    else
                        t = t->right;
                }
                return end();
            }

            iterator lower_bound(const key_type& item) {
                Node* t = _root;

                while (t != NULL) {
                    if (t->data.first == item)
                        return (iterator(t, this));
                    else if (Compare()(item, t->data.first))
                        return (iterator(t, this));
                    else
                        t = t->right;
                }
                return end();
            }

            const_iterator upper_bound(const key_type& item) const {
                Node* t = _root;

                while (t != NULL) {
                    if (Compare()(item, t->data.first))
                        return const_iterator(t, this);
                    else
                        t = t->right;
                }
                return end();
            }

            iterator upper_bound(const key_type& item) {
                Node* t = _root;

                while (t != NULL) {
                    if (Compare()(item, t->data.first))
                        return iterator(t, this);
                    else
                        t = t->right;
                }
                return end();
            }

			const_iterator end() const {
				return const_iterator(NULL, this);
			}

            iterator end() {
                return iterator(NULL, this);
            }

			Node* search(Node* root, key_type key) {
				if (root == NULL || root->key == key)
					return root;
				if (root->key < key)
					return search(root->right, key);
				return search(root->left, key);
			}
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

		typedef typename bstree::iterator           iterator;
		typedef typename bstree::const_iterator     const_iterator;
        typedef reverse_iterator<const_iterator>    const_reverse_iterator;
        typedef reverse_iterator<iterator> 		    reverse_iterator;

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

        iterator begin() {
            return _tree.begin();
        }
		const_iterator begin() const {
			return _tree.begin();
		}

		const_iterator end() const {
			return _tree.end();
		}

        iterator end() {
            return _tree.end();
        }

        reverse_iterator rbegin() {
            return (reverse_iterator(end()));
        }

        const_reverse_iterator rbegin() const {
            return (reverse_iterator(end()));
        }

        reverse_iterator rend() {
            return (reverse_iterator(begin()));
        }

        const_reverse_iterator rend() const {
            return (reverse_iterator(begin()));
        }


        bool empty() const { return !_size; }
		size_type size() const { return _size; }
		size_type max_size() const { return _alloc.max_size(); }

        pair<iterator, bool> insert(const value_type& val) {
            int isNew = 0;
			iterator temp = _tree.insert(val, isNew);
			if (!isNew)
				return (ft::make_pair<iterator, bool>(temp, false));
			_size++;
            pair<iterator, bool> t1 = ft::make_pair<iterator, bool>(temp, true);
			return (t1);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			InputIterator it = first;
            int isNew = 0;
			for (; it != last; it++) {
                _tree.insert(*it, isNew);
                if (isNew)
				    _size++;
                isNew = 0;
			}
		}

		iterator insert(iterator position, const value_type& val) {
			(void)position;
            int isNew = 0;
            iterator temp = _tree.insert(val, isNew);
            if (temp == _tree.end())
                return (temp);
            _size++;
            return (temp);
		}

		Alloc get_allocator() { return _alloc; }

		// Operator overloads
		mapped_type& operator[] (const key_type& k) {
            return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
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

		void swap(map& rhs) {
            std::swap(*this, rhs);
//            if (this != &rhs) {
//                _alloc = rhs._alloc;
//                _size = rhs._size;
//                _key_comp = rhs._key_comp;
//                _value_comp = rhs._value_comp;
//                iterator it = rhs.begin();
//                iterator ori_it = this->begin();
//                for (iterator it = rhs.begin(); it != rhs.end(); it++) {
//                    swap_value(ori_it->first, it->first);
//                    ori_it->second = it->second;
//                    ori_it++;
//                }
//            }
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

        iterator lower_bound (const key_type& k) {
            return _tree.lower_bound(k);
        }

        const_iterator lower_bound (const key_type& k) const {
            return _tree.lower_bound(k);
        }

        iterator upper_bound (const key_type& k) {
            return _tree.upper_bound(k);
        }

        const_iterator upper_bound (const key_type& k) const {
            return _tree.upper_bound(k);
        }

        pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
            return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
        }

        pair<iterator,iterator> equal_range (const key_type& k) {
            return (ft::make_pair<iterator , iterator>(lower_bound(k), upper_bound(k)));
        }

		size_type count(const key_type& k) const {
			if (_tree.find(k) != _tree.end())
				return 1;
			else
				return 0;
		}

        friend bool operator==(const map& lhs, const map& rhs) {
            if (lhs._size != rhs._size)
                return false;
            else
            {
                const_iterator it = lhs.begin();
                const_iterator it2 = rhs.begin();
                for (; it != lhs.end(); it++) {
                    if (it->second != it2->second)
                        return false;
                    it2++;
                }
            }
            return true;
        }
        friend bool operator!=(const map& lhs, const map& rhs) {
            return !(lhs == rhs);
        }
        friend bool operator< (const map& lhs, const map& rhs) {
            return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }
        friend bool operator> (const map& lhs, const map& rhs) {
            return (rhs < lhs);
        }
        friend bool operator>= (const map& lhs, const map& rhs) {
            return !(lhs < rhs);
        }
        friend bool operator<= (const map& lhs, const map& rhs) {
            return !(rhs < lhs);
        }
	};
}

#endif
