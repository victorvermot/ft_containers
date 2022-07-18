# include <map>
# include <iostream>
# include "Map.hpp"
# include "Pair.hpp"
# include <vector>

#define TESTED_NAMESPACE ft

int		main(void)
{
	std::vector<std::pair<int, std::string> > vectest;
	vectest.push_back(std::make_pair(5, "yolo1"));
	vectest.push_back(std::make_pair(6, "yolo2"));
	vectest.push_back(std::make_pair(7, "yolo3"));
	TESTED_NAMESPACE::map<int, std::string> test;
//	TESTED_NAMESPACE::map<int, std::string> test2(vectest.begin(), vectest.end());
	TESTED_NAMESPACE::map<int, std::string>::iterator it;
	it = test.begin();
	it->second = "swag";
	test.insert(TESTED_NAMESPACE::pair<int, std::string>(45, "swag"));
	test.insert(TESTED_NAMESPACE::pair<int, std::string>(0, "swagaaaa"));
	test.insert(TESTED_NAMESPACE::pair<int, std::string>(10, "10"));
	test[56] = "krool";
	std::cout << test[45] << std::endl;
//	for (it = test.begin(); it != test.end(); it++) {
//		std::cout << it->second << std::endl;
//	}
//	std::cout << (*it).first << std::endl;
//	std::cout << test.insert(std::pair<int, std::string>(1, "1")).first->first << std::endl;
//	std::cout << test.insert(std::pair<int, std::string>(5, "5")).first->first << std::endl;
//	std::cout << test.insert(std::pair<int, std::string>(-5, "-5")).first->first << std::endl;
//	std::cout << test.insert(std::pair<int, std::string>(0, "0")).first->first << std::endl;
//	std::cout << test.insert(std::pair<std::string, std::string>("Yolo54", "swag43")).second << std::endl;
//	test.insert(std::pair<std::string, std::string>("Yolo", "swag2"));

//	for (it = test.begin(); it != test.end(); it++) {
//		std::cout << it->second << std::endl;
//	}
	return (0);
}
