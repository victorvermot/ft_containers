#include <list>

#include "../base.hpp"
#if !defined(USING_STD)
# include "Map.hpp"
#else
# include <map>
#endif /* !defined(STD) */

#define _pair TESTED_NAMESPACE::pair

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
    o << "key: " << iterator->first << " | value: " << iterator->second;
    if (nl)
        o << std::endl;
    return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
    std::cout << "size: " << mp.size() << std::endl;
    std::cout << "max_size: " << mp.max_size() << std::endl;
    if (print_content)
    {
        typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
        std::cout << std::endl << "Content is:" << std::endl;
        for (; it != ite; ++it)
            std::cout << "- " << printPair(it, false) << std::endl;
    }
    std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void	printReverse(TESTED_NAMESPACE::map<T1, T2> &mp)
{
    typename TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

    std::cout << "printReverse:" << std::endl;
    while (it != ite) {
        it--;
        std::cout << "-> " << printPair(it, false) << std::endl;
    }
    std::cout << "_______________________________________________" << std::endl;
}


#define T1 int
#define T2 std::string
typedef _pair<const T1, T2> T3;

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
    std::cout << "\t-- [" << iter++ << "] --" << std::endl;
    std::cout << "ret: " << mp.erase(param) << std::endl;
    printSize(mp);
}

int		main(void)
{
    std::list<T3> lst;
    unsigned int lst_size = 6;
    for (unsigned int i = 0; i < lst_size; ++i)
        lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
    TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
    printSize(mp);

    for (int i = 2; i < 4; ++i)
        ft_erase(mp, i);

    ft_erase(mp, mp.begin()->first);
    ft_erase(mp, (--mp.end())->first);

    mp[-1] = "Hello";
    mp[10] = "Hi there";
    mp[10] = "Hi there";
    printSize(mp);

//    ft_erase(mp, 0);
    ft_erase(mp, 1);

    return (0);
}
