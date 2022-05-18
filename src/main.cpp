#include "../inc/Vector.hpp"
#include <vector>

int main()
{
	std::vector<int> ori(25, 5);
	ft::Vector<int> mine(25, 5);
	ft::Vector<int>::iterator it;
	ft::Vector<int>::iterator it2;
	std::vector<int>::iterator ori_it;
	ori_it = 1 + ori.begin();
	it = 1 + mine.begin();
	it2 = 1 + it;
	it2 += 1;
	*it = 5;
	it2[0] = 25;
	std::cout << *ori_it << std::endl;
	std::cout << mine[1] << std::endl;
}
