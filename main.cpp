#include "./inc/Vector.hpp"
#include <vector>

int main()
{
	ft::vector<int> ori(1, 2);
	std::vector<int> ori3(5, 6);
//	ft::vector<int>::iterator it = ori.begin();
//	ft::vector<int>::iterator it2 = ori.begin() + 3;
//	std::cout << it2 - it << std::endl;
//	ft::vector<int> ori2(3, 8);
//	ft::vector<int> ori2(3, 8);
//	ori.swap(ori2);
//	for (ft::vector<int>::iterator it = ori.begin(); it != ori.end(); it++) {
//		std::cout << "Before: " << *it << std::endl;
//	}
//	ori.assign<std::vector<int>::iterator>(ori3.begin(), ori3.begin() + 2);
//	ori.erase(ori.begin(), ori.begin() + 6);
	std::cout << "size: " << ori.size() << std::endl;
	ori.push_back(5);
//	ori.at(500);
	ori.insert(ori.begin() + 1, 20, 12);
	std::cout << "capacity: " << ori.capacity() << std::endl;
	for (ft::vector<int>::iterator it = ori.begin(); it != ori.end(); it++) {
		std::cout << *it << std::endl;
	}
//	ori.assign(2, 3);
//	ori.reserve(50);
//	std::cout << ori.capacity() << std::endl;
//	std::cout << ori.size() << std::endl;
//	for (std::vector<int>::iterator it = ori3.begin(); it != ori3.end(); it++) {
//		std::cout << *it << std::endl;
//	}

	return 0;
}
