#ifndef UnqPtr_hpp
#define UnqPtr_hpp
#include <stdio.h>
#include "MyDeleter.hpp"
#include "utility"
#include "MySwap"
#include "TraitsForArray.hpp"

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
        UnqPtr<T, MyDeleter> buf = UnqPtr<T, MyDeleter>;
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
    
    pointer operator()
    {
        return ptr;
    }
    
    //Array version
    template<typename U = T>
    enable_if_t<is_array<U>::value, std::remove_extent_t<U>&> operator[](std::size_t index) 
    {
        return ptr[index];
    }
    
    template<typename U = T>
    enable_if_t<is_array<U>::value, const std::remove_extent_t<U>&> operator[](std::size_t index) const 
    {
        return ptr[index];
    }

};

#endif
