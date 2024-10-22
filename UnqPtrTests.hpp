#pragma once
#include <cassert>
#include "UnqPtr.hpp"  // Подключаем ваш файл с реализацией UnqPtr
#include "MyDeleter.hpp"

// Тест на создание и разыменование указателя
void test_create_and_dereference() 
{
    UnqPtr<int> p1(new int(10));
    assert(p1.get() != nullptr);
    assert(*p1 == 10);
}

// Тест на перемещение указателя
void test_move_ptr() 
{
    UnqPtr<int> p1(new int(20));
    assert(p1.get() != nullptr);
    
    UnqPtr<int> p2 = std::move(p1);
    assert(p1.get() == nullptr);
    assert(p2.get() != nullptr);
    assert(*p2 == 20);
}

// Тест на операторы сравнения (==, !=, <, <=, >, >=)
void test_comparison_operators() 
{
    UnqPtr<int> p1(new int(30));
    UnqPtr<int> p2(new int(40));
    UnqPtr<int> p3 = std::move(p1);

    assert(p3 < p2 || p2 > p3);
    assert(p2 >= p3);
    assert(!(p3 >= p2));
}

// Тест на работу с массивами
void test_array_support() 
{
    auto pArray = UnqPtr<int[]>(new int[5]);
    for (int i = 0; i < 5; ++i) {
        pArray[i] = i;
    }
    for (int i = 0; i < 5; ++i) {
        assert(pArray[i] == i);
    }
}

// Тест на метод release
void test_release() 
{
    UnqPtr<int> p1(new int(50));
    int* raw_ptr = p1.realese();

    assert(p1.get() == nullptr);
    assert(raw_ptr != nullptr);

    delete raw_ptr;
}

// Тест на метод reset
void test_reset() 
{
    UnqPtr<int> p1(new int(60));
    assert(p1.get() != nullptr);
    
    p1.reset();
    assert(p1.get() == nullptr);
}

// Тест на проверку освобождения ресурса (метод IsFree)
void test_is_free() 
{
    UnqPtr<int> p1(new int(70));
    assert(!p1.IsFree());
    p1.reset();
    assert(p1.IsFree());
}

