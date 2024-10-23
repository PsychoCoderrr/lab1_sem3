#pragma once
#include "ShrdPtr.hpp"
#include "MySwap.hpp"
#include "MyDeleter.hpp"

template<typename T, class Ptr_Deleter = Deleter<T>>
class WeakPtr
{
    using K = remove_extent_t<T>;
private:
    using element_type = K;
    using pointer = K*;
    using deleter_type = Ptr_Deleter;
    pointer ptr;
    ControlBlock* count;
public:
    WeakPtr():ptr(nullptr), count(nullptr){};
    WeakPtr(const ShrdPtr<element_type, deleter_type>& incoming_pointer):ptr(incoming_pointer.ptr), count(incoming_pointer.count)
    {
        if (count != nullptr)
        {
            count->weak_count += 1;
        }
    }
    WeakPtr(const WeakPtr<element_type, deleter_type>& incoming_pointer):ptr(incoming_pointer.prt), count(incoming_pointer.count)
    {
        if(count != nullptr)
        {
            count->weak_count += 1;
        }
    }
    WeakPtr(WeakPtr<element_type, deleter_type>&& incoming_pointer):ptr(incoming_pointer.ptr), count(incoming_pointer.ptr)
    {
        incoming_pointer.ptr = nullptr;
        incoming_pointer.count = nullptr;
    }
    ~WeakPtr()
    {
        if (count == nullptr)
        {
            return;
        }
        count->weak_count -= 1;
        if(count->ref_count == 0 and count->ref_count == 0)
        {
            delete count;
        }
    }
    
    WeakPtr& operator=(const WeakPtr<element_type, deleter_type>& incoming_pointer)
    {
        if (ptr == incoming_pointer.ptr)
        {
            return *this;
        }
        WeakPtr<element_type, deleter_type> temp(incoming_pointer);
        swap(ptr, temp.ptr);
        swap(count, temp.count);
        return *this;
    }
    WeakPtr& operator=(WeakPtr<element_type, deleter_type>&& incoming_pointer)
    {
        if(ptr == incoming_pointer)
        {
            return *this;
        }
        swap(ptr, incoming_pointer.ptr);
        swap(count, incoming_pointer.count);
        return *this;
    }
    //Observers
    int use_count()
    {
        if(count == nullptr)
        {
            return 0;
        }
        return count->weak_count;
    }
    
    bool expired()
    {
        if (count == nullptr)
        {
            return true;
        }
        if(count->ref_count == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

