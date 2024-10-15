#ifndef MyDeleter_hpp
#define MyDeleter_hpp

#include <stdio.h>

template<typename T>
struct Deleter;

template<typename T>
struct Deleter<T[]>;

#endif
