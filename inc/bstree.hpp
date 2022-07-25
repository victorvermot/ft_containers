#ifndef CONTAINERS_BSTREE
# define CONTAINERS_BSTREE

# include <memory>
# include <functional>

template <typename T>
struct Node {

    typedef T value_type;

    value_type data;
    Node* left;
    Node* right;
    Node* parent;
    explicit Node(const value_type& newdata, Node* lt, Node* rt, Node* par) :
            data(newdata), left(lt), right(rt), parent (par) {
    }
};

template <typename T,
        typename Key,
        class Compare = std::less<Key>,
        typename nodeAlloc = std::allocator<Node<T> > >
class bstree {

public:

    typedef T data_type;
    typedef Node<data_type> val_node;
    typedef Key key_type;

private:

    val_node*       _root;
    nodeAlloc   _alloc;

    val_node* insert(val_node*& r, val_node* par, const data_type& data, int& isNew) {
        if (r == NULL) {
            r = _alloc.allocate(1);
            _alloc.construct(r, val_node(data, NULL, NULL, par));
//            r = new val_node(data, NULL, NULL, par);
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

    void makeEmpty(val_node*& r) {
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
        val_node* 	nodePtr;
        const bstree*	tree;

    public:

        typedef U value_type;
        typedef std::ptrdiff_t difference_type;
        typedef U* pointer;
        typedef U& reference;
        typedef bstIteratorTag iterator_category;

        bstIterator(val_node* p, const bstree* t) : nodePtr(p), tree(t) {}
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
            return (nodePtr == rhs.nodePtr);
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
            val_node* p;
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
            val_node* p;

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

        void swap_data(val_node* rhs) {
            nodePtr->data = rhs->data;
            nodePtr->right = rhs->right;
            nodePtr->left = rhs->left;
            nodePtr->parent = rhs->parent;
        }
    };

    typedef bstIterator<const data_type> const_iterator;
    typedef bstIterator<data_type> iterator;

    bstree() : _root(NULL) {}

    bstree(const bstree& other) : _root(NULL) {
        *this = other;
    }

    void setParent(val_node *r) {
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

    val_node* clone(val_node* r) {
        if (r == NULL)
            return NULL;
        else {
            val_node* ret = _alloc.allocate(1);
            _alloc.construct(ret, val_node(r->data, clone(r->left), clone(r->right), r->parent));
            return ret;
        }
    }

    iterator insert(const data_type& x, int& isNew) {
        val_node* temp = insert(_root, NULL, x, isNew);
        setParent(_root);
        return iterator(temp, this);
    }

    val_node* minValueNode(val_node* node) const {
        if (node == NULL)
            return NULL;
        if (node->left == NULL)
            return node;
        return minValueNode(node->left);
    }

    val_node* maxValueNode(val_node* node) const {
        val_node* current = node;

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

    void swap(bstree& rhs) {
        val_node* temp = this->_root;
        this->_root = rhs._root;
        rhs._root = temp;
    }

    bool deleteNode(val_node*& r, key_type key) {
        if (r == NULL)
            return false;
        if (Compare()(key, r->data.first)) {
            return deleteNode(r->left, key);
        }
        else if (Compare()(r->data.first, key)) {
            return deleteNode(r->right, key);
        }
        else if (r->left != NULL && r->right != NULL) {
            val_node* test = maxValueNode(r->left);
            val_node* temp = r;
            r = _alloc.allocate(1);
            _alloc.construct(r, val_node(test->data, temp->left, temp->right, temp->parent));
            _alloc.deallocate(temp, 1);
            setParent(r);
            deleteNode(r->left, r->data.first);
            return true;
        }
        else {
            val_node* temp = r;
            r = (r->left != NULL) ? r->left : r->right;
            if (r)
                r->parent = temp->parent;
            _alloc.deallocate(temp, 1);
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
        val_node* t = _root;
        while (t != NULL && !(t->data.first == item)) {
            if (Compare()(item, t->data.first))
                t = t->left;
            else
                t = t->right;
        }
        return const_iterator(t, this);
    }

    iterator find(const key_type& item) {
        val_node* t = _root;
        while (t != NULL && !(t->data.first == item)) {
            if (Compare()(item, t->data.first))
                t = t->left;
            else
                t = t->right;
        }
        return iterator(t, this);
    }

    const_iterator lower_bound(const key_type& item) const {
        val_node* t = _root;

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
        val_node* t = _root;

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
        val_node* t = _root;

        while (t != NULL) {
            if (Compare()(item, t->data.first))
                return const_iterator(t, this);
            else
                t = t->right;
        }
        return end();
    }

    iterator upper_bound(const key_type& item) {
        val_node* t = _root;

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

    val_node* search(val_node* root, key_type key) {
        if (root == NULL || root->key == key)
            return root;
        if (root->key < key)
            return search(root->right, key);
        return search(root->left, key);
    }
};

#endif //FT_CONTAINERS_BSTREE_HPP
