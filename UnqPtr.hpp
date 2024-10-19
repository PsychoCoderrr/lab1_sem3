#ifndef UnqPtr_hpp
#define UnqPtr_hpp
#include <stdio.h>
#include "MyDeleter.hpp"
#include "utility"

template<typename T, typename Ptr_Deleter = Deleter<T>>
class UnqPtr
{
private:
    using element_type = T;
    using pointer = element_type*;
    using deleter_type = Ptr_Deleter;
    pointer ptr;
    deleter_type del = deleter_type();
public:
    UnqPtr(): ptr(nullptr) {};
    UnqPtr(pointer other):ptr(std::move(other)) {};
    UnqPtr(const UnqPtr<element_type, deleter_type>& other) = delete;
    UnqPtr(UnqPtr<element_type, deleter_type>&& other):ptr(other)
    {
        other.ptr = nullptr;
    }
    virtual ~UnqPtr()
    {
        del(ptr);
    }
    
    
    bool IsFree()
    {
        if (ptr == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

#endif
