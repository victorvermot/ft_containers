#include "./inc/Vector.hpp"
#include <vector>
#define TESTED_NAMESPACE std
#define TESTED_TYPE int

void printSize(TESTED_NAMESPACE::vector<TESTED_TYPE> const &ori, bool cap) {
	cap = true;
	std::cout << "size: " << ori.size() << std::endl;
	std::cout << "capacity: " << ori.capacity() << std::endl;
	std::cout << "max size: " << ori.max_size() << std::endl;
	if (cap)
	{
		typename TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator it = ori.begin();
		typename TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator ite = ori.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
}

void	is_empty(std::vector<int> const &vct)
{
	std::cout << "is_empty: " << vct.empty() << std::endl;
}


int main()
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct.at(): " << vct.at(i) << " | ";
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	printSize(vct, true);

	TESTED_NAMESPACE::vector<TESTED_TYPE> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	try {
		vct.at(10) = 42;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
	return (0);
}
//vct.at(): 21 | vct[]: 21
//vct.at(): 18 | vct[]: 18
//vct.at(): 15 | vct[]: 15
//vct.at(): 12 | vct[]: 12
//vct.at(): 9 | vct[]: 9
//vct.at(): 6 | vct[]: 6
//vct.at(): 3 | vct[]: 3
//size: 7
//capacity: 7
//max size: 4611686018427387903
//
//Content is:
//- 21
//- 18
//- 15
//- 12
//- 9
//- 6
//- 3
//front(): 21 21
//back(): 3 3
//Catch out_of_range exception!