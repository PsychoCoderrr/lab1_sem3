#pragma once
#include <iostream>
#include <type_traits>

template<typename T>
struct is_array : std::false_type {};

template<typename T>
struct is_array<T[]> : std::true_type {};

template<typename T, std::size_t N>
struct is_array<T[N]> : std::true_type {};

// Алиас для удобства
template<typename T>
using is_array_t = typename is_array<T>::type;

// enable_if для активации определённых частей кода
template<bool B, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> {
    using type = T;
};

// Алиас для enable_if
template<bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;
