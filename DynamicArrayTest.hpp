#pragma once
#include <cassert>
#include <iostream>
#include "DynamicArray.hpp"

// Тесты
void test_empty_array() {
    DynamicArray<int> arr;
    assert(arr.GetSize() == 0);
    std::cout << "test_empty_array passed.\n";
}

void test_array_with_size() {
    DynamicArray<int> arr(5);
    assert(arr.GetSize() == 5);
    std::cout << "test_array_with_size passed.\n";
}

void test_array_with_elements() {
    int initial_elements[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr(initial_elements, 5);
    assert(arr.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        assert(arr.Get(i) == initial_elements[i]);
    }
    std::cout << "test_array_with_elements passed.\n";
}

void test_get_method() {
    int initial_elements[] = {10, 20, 30};
    DynamicArray<int> arr(initial_elements, 3);
    assert(arr.Get(0) == 10);
    assert(arr.Get(1) == 20);
    assert(arr.Get(2) == 30);
    std::cout << "test_get_method passed.\n";
}

void test_set_method() {
    DynamicArray<int> arr(3);
    arr.Set(100, 0);
    arr.Set(200, 1);
    arr.Set(300, 2);
    assert(arr.Get(0) == 100);
    assert(arr.Get(1) == 200);
    assert(arr.Get(2) == 300);
    std::cout << "test_set_method passed.\n";
}

void test_index_operator() {
    DynamicArray<int> arr(4);
    arr.Set(10, 0);
    arr.Set(20, 1);
    arr.Set(30, 2);
    arr.Set(40, 3);
    assert(arr[0] == 10);
    assert(arr[1] == 20);
    assert(arr[2] == 30);
    assert(arr[3] == 40);
    arr[1] = 100;  // Изменение значения через оператор []
    assert(arr[1] == 100);
    std::cout << "test_index_operator passed.\n";
}

void test_resize() {
    DynamicArray<int> arr(3);
    arr.Set(1, 0);
    arr.Set(2, 1);
    arr.Set(3, 2);
    
    arr.Resize(5);  // Увеличиваем размер массива
    assert(arr.GetSize() == 5);
    
    arr.Resize(2);  // Уменьшаем размер массива
    assert(arr.GetSize() == 2);
    
    try {
        arr.Get(4);  // Проверяем, что доступ за границы вызывает исключение
        assert(false);  // Если сюда дошли, значит ошибка
    } catch (const std::out_of_range&) {
        std::cout << "test_resize passed.\n";
    }
}

void test_exceptions() {
    try {
        DynamicArray<int> arr(-5);  // Попытка создать массив с отрицательным размером
        assert(false);  // Если сюда дошли, значит ошибка
    } catch (const std::invalid_argument&) {
        std::cout << "Caught invalid_argument for negative size.\n";
    }

    DynamicArray<int> arr(3);
    try {
        arr.Get(10);  // Попытка получить элемент с некорректным индексом
        assert(false);  // Если сюда дошли, значит ошибка
    } catch (const std::out_of_range&) {
        std::cout << "Caught out_of_range for invalid index.\n";
    }

    try {
        arr.Set(100, 10);  // Попытка установить элемент с некорректным индексом
        assert(false);  // Если сюда дошли, значит ошибка
    } catch (const std::out_of_range&) {
        std::cout << "Caught out_of_range for invalid set index.\n";
    }

    std::cout << "test_exceptions passed.\n";
}
