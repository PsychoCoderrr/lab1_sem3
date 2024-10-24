#pragma once
#include "UnqPtr.hpp"
#include <memory>

template<typename T>
class DynamicArray
{
private:
    UnqPtr<T[]> elements;
    int size;
    int capacity;
    inline void Reserve(int newCapacity)
    {
        if (newCapacity <= capacity)
        {
            capacity = newCapacity;
            return;
        }

        UnqPtr<T[]> newElements = UnqPtr<T[]>(new int[newCapacity]);
        for (int i = 0; i < size; i++)
        {
            newElements[i] = elements[i];
        }
        elements.reset();
        elements = std::move(newElements);
        capacity = newCapacity;
    }
public:
    DynamicArray(): elements(nullptr), size(0), capacity(0){};
    DynamicArray(int size):size(size), capacity(size * 2)
    {
            if(size<0)
                throw std::invalid_argument("invalid argument");
            if(size>0)
                elements = UnqPtr<T[]>(new T[size]);
        }
    DynamicArray( const UnqPtr<T[]>& items, int count):DynamicArray(count)
    {
        if(items==nullptr)
        {
            throw std::invalid_argument("invalid argument");
        }
        for (int i = 0; i < count; i++)
        {
            elements[i] = items[i];
        }
        
    }
    DynamicArray(const T* ptr , int count):DynamicArray(count)
    {
        if(ptr==nullptr){
            throw std::invalid_argument("invalid argument");
        }
        for(int i=0;i<count;i++)
        {
            elements[i]=ptr[i];
        }
    }
    virtual ~DynamicArray() = default;
    
    T& operator[](int index)
    {
        if(size<=index || size < 0)
        {
            throw std::out_of_range("Invalid index");
        }
        return elements[index];
    }
    
    const T& operator[](int index) const
    {
        if(size<=index || size < 0)
        {
            throw std::out_of_range("Invalid index");
        }
        return elements[index];
    }
    T Get(int index) const 
    {
        if(size<=index||index<0)
        {
            throw std::out_of_range("Invalid index");
        }
        return elements[index];
    }
    int GetSize() const
    {
        return size;
    }
    void Set(const T& value,int index) 
    {
        if(size<=index || index<0)
        {
            throw std::out_of_range("Invalid index");
        }
        elements[index]=value;
    }
    void Resize(int newSize)
    {
        if (newSize < 0)
        {
            throw std::invalid_argument("invalid argument");
        }
        if (newSize == 0)
        {
            elements.reset();
        }
        if (newSize > capacity)
        {
            Reserve(newSize * 2);
        }
        size = newSize;
    }
};
