//
// Created by Victor Vermot-petit-outhenin on 6/26/22.
//

#ifndef SWAP_HPP
# define SWAP_HPP

namespace ft {
	template<typename T>
	void	swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}
}

#endif
