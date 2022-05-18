#ifndef PAIR_H
# define PAIR_H

template<typename T1, typename T2>
class pair {
private:
	typedef T1 first_type;
	typedef T2 second_type;

public:
	first_type 	first;
	second_type second;

	pair();

	template<class U, class V>
	pair (const pair<U, V>& pr) { *this = other; }

	pair(const first_type& a, const second_type& b) : first(a), second(b) {}

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	template <class T1,class T2>
	pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y));
	}

	pair &operator=(const Pair &rhs) {
		this->first = rhs.first;
		this->second = rhs.second;
		return (*this);
	};
	~pair();
};


#endif
