#pragma once
#include <type_traits>
#include <stdio.h>
#include "MyDeleter.hpp"
#include <utility>
#include "MySwap.hpp"
#include "TraitsForArrays.hpp"
#define BAD_TYPE 100;
template<typename T, typename Ptr_Deleter = Deleter<T>>
class UnqPtr
{
    using K = remove_extent_t<T>;
private:
    using element_type = K;
    using pointer = element_type*;
    using deleter_type = Ptr_Deleter;
    pointer ptr;
    deleter_type del = deleter_type();
    inline void MySwap(UnqPtr& incoming_pointer)
    {
        swap(ptr, incoming_pointer.ptr);
    }
public:
    UnqPtr(): ptr(nullptr) {};
    UnqPtr(pointer other):ptr(std::move(other)) {};
    UnqPtr(const UnqPtr<element_type, deleter_type>& other) = delete;
    UnqPtr(UnqPtr&& other):ptr(other.ptr)
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
        MySwap(buf);
    }
    
    //Observers
    pointer get()
    {
        return ptr;
    }
    const pointer get() const
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
    element_type& operator *()
    {
        return *ptr;
    }
    
    pointer operator->()
    {
        return ptr;
    }
    
    template <typename U = T>
    K& operator [](int index)&
    {
        if (is_array<U>::type)
        {
            return ptr[index];
        }
        else
        {
            throw BAD_TYPE;
        }
    }
    
    template <typename U = T>
    const K& operator [](int index) const
    {
        if (is_array<U>::type)
        {
            return ptr[index];
        }
        else
        {
            throw BAD_TYPE;
        }
    }
    
    UnqPtr& operator=(UnqPtr<T, deleter_type>&& incoming_pointer)
    {
        UnqPtr<T,deleter_type> temp_ptr(std::move(incoming_pointer));
        MySwap(temp_ptr);
        return *this;
    }
};

template<typename T,class Ptr_Deleter = Deleter<T>>
UnqPtr<T[],Ptr_Deleter> make_unique(size_t size)
{
    T* ptr = new T[size];
    return unique_ptr<T,Ptr_Deleter>(ptr);
}

template<typename T, class Ptr_Deleter = Deleter<T>, typename... Args>
UnqPtr<T[], Ptr_Deleter> make_unique(int size, Args&&... args)
{
    T*ptr = new T[size];
    for(int i = 0; i < size; i++)
    {
        ptr[i] = T(args...);
    }
    return UnqPtr<T[], Ptr_Deleter>(ptr);
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
    if (lhs.get() > rhs.get())
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
    if (lhs.get() >= rhs.get())
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
    if (lhs.get() < rhs.get())
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
