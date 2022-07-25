# include "map.hpp"
# include "vector.hpp"
# include "stack.hpp"
# include <list>

# define TESTED_NAMESPACE ft

int		main(void)
{
    std::list<ft::pair<int, std::string> > std_list;
    for (int i = 0; i < 500; i++) {
        std_list.push_back(ft::make_pair<int, std::string>(i, "swag"));
    }

    TESTED_NAMESPACE::map<int, std::string> my_map(std_list.begin(), std_list.end());

    std::cout << "Hello World" << std::endl;
    return (0);
}
