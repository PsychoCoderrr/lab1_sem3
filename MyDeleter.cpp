#include "MyDeleter.hpp"
#include <stdio.h>

template<typename T>
void
Deleter<T>::operator()(T* ptr)
{
    delete ptr;
}


template<typename T>
void
Deleter<T[]>::operator()(T* ptr)
{
    delete[] ptr;
};
