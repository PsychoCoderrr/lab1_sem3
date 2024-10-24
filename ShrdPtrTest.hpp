#pragma once
#include <cassert>
#include <iostream>
#include "ShrdPtr.hpp"

// Простой класс для тестов
class TestObject
{
public:
    int value;
    TestObject(int val) : value(val) {}
};

void test_empty_shared_ptr() {
    ShrdPtr<int> ptr;
    assert(ptr.get() == nullptr);
    assert(ptr.use_count() == 0);
    std::cout << "test_empty_shared_ptr passed.\n";
}

void test_shared_ptr_with_object() {
    ShrdPtr<int> ptr(new int(10));
    assert(ptr.get() != nullptr);
    assert(*ptr == 10);
    assert(ptr.use_count() == 1);
    std::cout << "test_shared_ptr_with_object passed.\n";
}

void test_shared_ptr_copy() {
    ShrdPtr<int> ptr1(new int(20));
    ShrdPtr<int> ptr2 = ptr1;
    assert(ptr1.get() == ptr2.get());
    assert(ptr1.use_count() == 2);
    assert(ptr2.use_count() == 2);
    std::cout << "test_shared_ptr_copy passed.\n";
}

void test_shared_ptr_move() {
    ShrdPtr<int> ptr1(new int(30));
    ShrdPtr<int> ptr2 = std::move(ptr1);
    assert(ptr1.get() == nullptr);
    assert(ptr2.get() != nullptr);
    assert(*ptr2 == 30);
    assert(ptr2.use_count() == 1);
    std::cout << "test_shared_ptr_move passed.\n";
}

void test_shared_ptr_reset() {
    ShrdPtr<int> ptr(new int(40));
    ptr.reset();
    assert(ptr.get() == nullptr);
    assert(ptr.use_count() == 0);
    std::cout << "test_shared_ptr_reset passed.\n";
}

void test_shared_ptr_use_count() {
    ShrdPtr<int> ptr1(new int(50));
    assert(ptr1.use_count() == 1);
    ShrdPtr<int> ptr2 = ptr1;
    assert(ptr1.use_count() == 2);
    ptr2.reset();
    assert(ptr1.use_count() == 1);
    std::cout << "test_shared_ptr_use_count passed.\n";
}

void test_shared_ptr_dereference() {
    ShrdPtr<TestObject> ptr(new TestObject(100));
    assert(ptr->value == 100);
    assert((*ptr).value == 100);
    std::cout << "test_shared_ptr_dereference passed.\n";
}

