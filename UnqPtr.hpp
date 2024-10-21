#pragma once

#include <stdio.h>
#include "MyDeleter.hpp"
#include "utility"
#include "MySwap.hpp"
#include "TraitsForArrays.hpp"

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
    
    
    //Modifiers
    pointer realese()
    {
        pointer buf = ptr;
        ptr = nullptr;
        return buf;
    }
    void reset()
    {
        UnqPtr<T, deleter_type> buf = UnqPtr<T, deleter_type>();
        my_swap(ptr, buf.ptr);
    }
    
    //Observers
    pointer get()
    {
        return ptr;
    }
    deleter_type& get_deleter()
    {
        return del;
    }
    const deleter_type& get_deleter() const
    {
        return del;
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
    }
    
    //Single-object version
    T& operator *()
    {
        return *ptr;
    }
    
    pointer operator->()
    {
        return ptr;
    }
    
    //Array version
    template<typename U = element_type>
    enable_if_t<is_array<U>::value, std::remove_extent_t<U>&> operator[](std::size_t index)
    {
        return ptr[index];
    }
    
    template<typename U = element_type>
    enable_if_t<is_array<U>::value, const std::remove_extent_t<U>&> operator[](std::size_t index) const
    {
        return ptr[index];
    }
};

// Non-member functions
template<typename T, class Ptr_Deleter = Deleter<T>>
UnqPtr<T, Ptr_Deleter> make_unique(int size)
{
    T*ptr = new T[size];
    return UnqPtr<T, Ptr_Deleter>(ptr);
}

template<typename T, class Ptr_Deleter = Deleter<T>, typename... Args>
UnqPtr<T, Ptr_Deleter> make_unique(int size, Args&&... args)
{
    T*ptr = new T[size];
    for(int i = 0; i < size; i++)
    {
        ptr[i] = T(args...);
    }
    return UnqPtr<T, Ptr_Deleter>(ptr);
}

template<typename T, class Ptr_Deleter = Deleter<T>>
bool operator ==(UnqPtr<T, Ptr_Deleter> lhs, UnqPtr<T, Ptr_Deleter> rhs)
{
    if (lhs.get == rhs.get)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T, class Ptr_Deleter = Deleter<T>>
bool operator != (UnqPtr<T, Ptr_Deleter> lhs, UnqPtr<T, Ptr_Deleter> rhs)
{
    if (lhs.get != rhs.get)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T, class Ptr_Deleter = Deleter<T>>
bool operator>(const UnqPtr<T, Ptr_Deleter>& lhs, const UnqPtr<T, Ptr_Deleter>& rhs) {
    if (lhs.get() > rhs.get)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T, class Ptr_Deleter = Deleter<T>>
bool operator>=(const UnqPtr<T, Ptr_Deleter>& lhs, const UnqPtr<T, Ptr_Deleter>& rhs) {
    if (lhs.get() >= rhs.get)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T, class Ptr_Deleter = Deleter<T>>
bool operator<(const UnqPtr<T, Ptr_Deleter>& lhs, const UnqPtr<T, Ptr_Deleter>& rhs) {
    if (lhs.get() < rhs.get)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T, class Ptr_Deleter = Deleter<T>>
bool operator<=(const UnqPtr<T, Ptr_Deleter>& lhs, const UnqPtr<T, Ptr_Deleter>& rhs) {
    if (lhs.get() <= rhs.get)
    {
        return true;
    }
    else
    {
        return false;
    }
}
