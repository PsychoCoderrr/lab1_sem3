#include <cassert>
#include <iostream>
#include "ShrdPtr.hpp"
#include "WeakPtr.hpp"

// Простой класс для тестов

void test_empty_weak_ptr() {
    WeakPtr<int> wptr;
    assert(wptr.use_count() == 0);
    assert(wptr.expired());
    std::cout << "test_empty_weak_ptr passed.\n";
}

void test_weak_ptr_from_shared() {
    ShrdPtr<int> sptr(new int(10));
    WeakPtr<int> wptr(sptr);
    assert(wptr.use_count() == 1);
    assert(!wptr.expired());
    std::cout << "test_weak_ptr_from_shared passed.\n";
}

void test_weak_ptr_copy() {
    ShrdPtr<int> sptr(new int(20));
    WeakPtr<int> wptr1(sptr);
    WeakPtr<int> wptr2 = wptr1;
    assert(wptr1.use_count() == 2);
    assert(wptr2.use_count() == 2);
    assert(!wptr1.expired());
    assert(!wptr2.expired());
    std::cout << "test_weak_ptr_copy passed.\n";
}

void test_weak_ptr_move() {
    ShrdPtr<int> sptr(new int(30));
    WeakPtr<int> wptr1(sptr);
    WeakPtr<int> wptr2 = std::move(wptr1);
    assert(wptr1.use_count() == 0); 
    assert(wptr2.use_count() == 1);
    assert(wptr1.expired());
    assert(!wptr2.expired());
    std::cout << "test_weak_ptr_move passed.\n";
}

void test_weak_ptr_assignment() {
    ShrdPtr<int> sptr1(new int(40));
    WeakPtr<int> wptr1(sptr1);

    ShrdPtr<int> sptr2(new int(50));
    WeakPtr<int> wptr2(sptr2);

    wptr1 = wptr2;
    assert(wptr1.use_count() == 2);
    assert(wptr2.use_count() == 2);
    assert(!wptr1.expired());
    assert(!wptr2.expired());
    std::cout << "test_weak_ptr_assignment passed.\n";
}

void test_weak_ptr_expired() {
    ShrdPtr<int> sptr(new int(60));
    WeakPtr<int> wptr(sptr);
    assert(!wptr.expired());
    sptr.reset();
    assert(wptr.expired());
    std::cout << "test_weak_ptr_expired passed.\n";
}


