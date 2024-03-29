#ifndef FT_CONTAINERS_STACK_HPP
# define FT_CONTAINERS_STACK_HPP

# include "vector.hpp"

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack {

	public:

		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t 		size_type;

	private:

		container_type _ctnr;

	public:
		explicit stack(const container_type& ctnr = container_type()) {
            this->_ctnr = ctnr;
		}
		bool empty() const {
			return _ctnr.empty();
		}
		size_type size() const {
			return _ctnr.size();
		}
		value_type& top() {
			return _ctnr.back();
		}
		const value_type& top() const {
			return _ctnr.back();
		}
		void push(const value_type& val) {
			_ctnr.push_back(val);
		}
		void pop() {
			_ctnr.pop_back();
		}

		friend bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr == rhs._ctnr;
		}
		friend bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr != rhs._ctnr;
		}
		friend bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr < rhs._ctnr;
		}
		friend bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr <= rhs._ctnr;
		}
		friend bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr > rhs._ctnr;
		}
		friend bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return lhs._ctnr >= rhs._ctnr;
		}

		~stack() {};

	};
}


#endif //FT_CONTAINERS_STACK_HPP
