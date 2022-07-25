#ifndef MAP_H
# define MAP_H
# include "pair.hpp"
# include <memory>
# include <functional>
# include "reverse_iterator.hpp"
# include "lexicographical_compare.hpp"
# include "bstree.hpp"

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

	private:

		key_compare _key_comp;
		Alloc		_alloc;
		bstree<value_type, key_type, Compare>    _tree;
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

        typedef bstree<value_type, key_type, Compare> bst;
		typedef typename bst::iterator           iterator;
		typedef typename bst::const_iterator     const_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
        typedef ft::reverse_iterator<iterator> 		    reverse_iterator;

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
//            pair<iterator, bool> t1 = ft::make_pair<iterator, bool>(temp, true);
			return (ft::make_pair<iterator, bool>(temp, true));
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
            if (this != &rhs) {
                std::swap(_alloc, rhs._alloc);
                std::swap(_size, rhs._size);
                std::swap(_key_comp, rhs._key_comp);
                std::swap(_value_comp, rhs._value_comp);
                _tree.swap(rhs._tree);
            }
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
