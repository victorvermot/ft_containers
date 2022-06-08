#include "../inc/Vector.hpp"
#include <vector>

int main()
{
//	std::vector<int> ori(25, 5);
//	ft::Vector<int> mine(25, 5);
////	ft::Vector<int>::iterator it;
////	ft::Vector<int>::iterator it2;
////	std::vector<int>::iterator ori_it;
////	ori_it = 1 + ori.begin();
////	it = 1 + mine.begin();
////	it2 = 1 + it;
////	it2 += 1;
////	*it = 5;
////	it2[0] = 25;
////	std::cout << *ori_it << std::endl;
////	std::cout << mine[1] << std::endl;
//	std::cout << mine.size() << std::endl;
//	mine.resize(5, 2);
//	std::cout << ori.max_size() << std::endl;
//	std::cout << mine.size() << std::endl;

	ft::Vector<int> foo (3,100);   // three ints with a value of 100
	ft::Vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';

	return 0;
}
