#pragma once
#include <iostream>
#include <type_traits>

template <class T>
struct remove_extent {
    using type = T;
};

template <class T, size_t N>
struct remove_extent<T[N]> {
    using type = T;
};

template <class T>
struct remove_extent<T[]> {
    using type = T;
};

template <class T>
using remove_extent_t = typename remove_extent<T>::type;


template<typename T>
struct is_array {bool type = false;};

template<typename T>
struct is_array<T[]> {static const bool type = true;};

template<typename T, std::size_t N>
struct is_array<T[N]> {static const bool type = true;};





