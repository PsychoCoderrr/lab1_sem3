#ifndef MyDeleter_hpp
#define MyDeleter_hpp

#include <stdio.h>

template<typename T>
struct Deleter
{
    void operator()(T* ptr);
};


template<typename T>
struct Deleter<T[]>
{
    void operator()(T* ptr);
};

#endif
