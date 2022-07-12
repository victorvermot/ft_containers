#ifndef PAIR_H
# define PAIR_H


namespace ft {

	template<typename T1, typename T2>
	class pair {
	private:
		typedef T1 first_type;
		typedef T2 second_type;

	public:
		first_type 	first;
		second_type second;

		pair() {};

		pair(const pair& other) { *this = other; }

		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		friend bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

		friend bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs != rhs; }

		friend bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first < rhs.first || (rhs.first >= lhs.first && lhs.second < rhs.second); }

		friend bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

		friend bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

		friend bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }

		pair &operator=(const pair &rhs) {
			if (this != &rhs) {
				this->first = rhs.first;
				this->second = rhs.second;
			}
			return (*this);
		};
		~pair() {};
	};
	template <class T1,class T2>
	pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y));
	}
}


#endif
