//
// Created by Victor Vermot-petit-outhenin on 5/16/22.
//

#include <vector>
#include <iostream>

int main()
{
	std::vector<int> a(5, 6);
	std::vector<int>::iterator it1;
	std::vector<int>::iterator it2;
	it1 = a.begin();
	it2 = it1 + 50;
	bool big = *it1 < *it2;
	std::cout << big << std::endl;
	std::cout << *it1 << std::endl;
	std::cout << *it2 << std::endl;

}
