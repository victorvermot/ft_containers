#include "./inc/Vector.hpp"
#include <vector>
#define TESTED_NAMESPACE ft
#define TESTED_TYPE int

int main() {
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; i++) {
		vct[i] = i;
		std::cout << vct[i] << std::endl;
	}
	std::cout << "-------------------------" << std::endl;
	for (int i = 0; i < size; ++i) {
		std::cout << it[1] << std::endl;
		it[i] = (size - i) * 5;
		std::cout << it[i] << std::endl;
	}
}
