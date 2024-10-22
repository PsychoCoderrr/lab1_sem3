#pragma once
#include "MySwap.hpp"

struct ControlBlock
{
    int ref_count;
    int weak_count;
    ControlBlock(int ref = 0, int weak = 0): ref_count(0), weak_count(0){};
};

template<typename T, typename Ptr_Deleter = Deleter<T>>
class WeakPtr{};

template<typename T, typename Ptr_Deleter = Deleter<T>>
class ShrdPtr
{
    using K = remove_extent_t<T>;
private:
    using element_type = K;
    using pointer = element_type*;
    using deleter_type = Ptr_Deleter;
    pointer ptr;
    ControlBlock* count;
    friend class WeakPtr<T, deleter_type>;
public:
    //Constructors
    ShrdPtr():ptr(nullptr), count(nullptr){};
    ShrdPtr(pointer incoming_pointer):ptr(std::move(incoming_pointer))
    {
        if(ptr != nullptr)
        {
            count = new ControlBlock(1, 0);
        }
        else
        {
            count = nullptr;
        }
    }
    ShrdPtr(WeakPtr<T, deleter_type>& incoming_pointer):ptr(incoming_pointer.ptr), count(incoming_pointer.count)
    {
        if (count != nullptr)
        {
            count->ref_count++;
        }
    }
    ShrdPtr(ShrdPtr<element_type, deleter_type>& incoming_pointer)
    {
        ptr = incoming_pointer.ptr;
        count = incoming_pointer.count;
        if(count != nullptr)
        {
            count->ref_count++;
        }
    }
    ShrdPtr(ShrdPtr<element_type, deleter_type>&& incoming_pointer): ptr(incoming_pointer.ptr), count(incoming_pointer.ptr)
    {
        incoming_pointer.ptr = nullptr;
        incoming_pointer.count = nullptr;
    }
    //Destructor
    ~ShrdPtr()
    {
        if (count != nullptr)
        {
            return;
        }
        count->ref_count --;
        if(count->ref_count == 0)
        {
            deleter_type func_delete = deleter_type();
            func_delete(ptr);
            if(count->weak_count == 0)
            {
                delete count;
            }
        }
    }
    
    element_type& operator =(const ShrdPtr<element_type, deleter_type>& incoming_pointer)
    {
        if(ptr == incoming_pointer.ptr)
        {
            return *this;
        }
        ShrdPtr<element_type, deleter_type> temp(incoming_pointer);
        swap(ptr, temp.ptr);
        swap(count, temp.count);
        return *this;
    }
    
    element_type& operator =(ShrdPtr<element_type, deleter_type>&& incoming_pointer)
    {
        if (ptr == incoming_pointer)
        {
            return *this;
        }
        ShrdPtr<element_type, deleter_type> temp(incoming_pointer);
        swap(ptr, temp.ptr);
        swap(count, temp.count);
        return *this;
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
    
    //Modifiers
    void reset()
    {
        ShrdPtr<element_type, deleter_type> buf = ShrdPtr<element_type, deleter_type>();
        swap(buf.ptr, ptr);
        swap(buf.count, count);
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
    
    const element_type& operator*() const
    {
        return *ptr;
    }
    
    const pointer operator->() const
    {
        return ptr;
    }
    
};

