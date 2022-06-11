#ifndef FT_CONTAINERS_IS_INTEGRAL_HPP
# define FT_CONTAINERS_IS_INTEGRAL_HPP


namespace ft {
	template<class T>
	class is_integral {
	public:
		static const bool value = false;
	};

	template<>
	class is_integral<int> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<bool> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<char> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<wchar_t> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<signed char> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<short int> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<long int> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<unsigned char> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<unsigned short int> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<unsigned int> {
	public:
		static const bool value = true;
	};

	template<>
	class is_integral<unsigned long int> {
	public:
		static const bool value = true;
	};
}


#endif //FT_CONTAINERS_IS_INTEGRAL_HPP
