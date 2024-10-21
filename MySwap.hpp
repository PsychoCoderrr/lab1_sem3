#pragma once

#include <stdio.h>
#include "utility"

template<typename T>
void swap(T& a, T&b)
{
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(a);
}


