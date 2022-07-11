# include <map>
# include <iostream>

int		main(void)
{
	std::map<int, std::string> test;
	std::map<int, std::string>::iterator it;
	std::cout << test.insert(std::pair<int, std::string>(1, "1")).first->first << std::endl;
	std::cout << test.insert(std::pair<int, std::string>(5, "5")).first->first << std::endl;
	std::cout << test.insert(std::pair<int, std::string>(-5, "-5")).first->first << std::endl;
	std::cout << test.insert(std::pair<int, std::string>(0, "0")).first->first << std::endl;
//	std::cout << test.insert(std::pair<std::string, std::string>("Yolo54", "swag43")).second << std::endl;
//	test.insert(std::pair<std::string, std::string>("Yolo", "swag2"));

	for (it = test.begin(); it != test.end(); it++) {
		std::cout << it->second << std::endl;
	}
	return (0);
}
