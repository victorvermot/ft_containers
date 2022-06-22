cmake_minimum_required(VERSION 3.22)
project(ft_containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

add_executable(ft_containers
        inc/enable_if.hpp
        inc/is_integral.hpp
        inc/Iterator.hpp
        inc/IteratorTraits.hpp
        inc/Map.hpp
        inc/Pair.hpp
        inc/RaIterator.hpp
        inc/ReverseIterator.hpp
        inc/Vector.hpp
        src/main_official.cpp
        src/test.cpp
        main.cpp)
