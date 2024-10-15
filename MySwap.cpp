#include "MySwap.hpp"
#include <utility>
#include <stdio.h>
template<typename T>
void swap(T& a, T&b)
{
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(a);
}


