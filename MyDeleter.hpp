#pragma once
#include <stdio.h>

template<typename T>
struct Deleter
{
    void operator()(T* ptr)
    {
        
        delete ptr;
    }
};


template<typename T>
struct Deleter<T[]>
{
    void operator()(T* ptr)
    {
        delete[] ptr;
    };
};
