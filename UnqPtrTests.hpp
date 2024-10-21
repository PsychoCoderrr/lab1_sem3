#pragma once
#include <cassert>
#include "UnqPtr.hpp"  // Подключаем ваш файл с реализацией UnqPtr
#include "MyDeleter.hpp"

// Тест на создание и разыменование указателя
void test_create_and_dereference() {
    UnqPtr<int> p1(new int(10));  // Создаем UnqPtr, управляющий int
    assert(p1.get() != nullptr);  // Убедимся, что указатель не nullptr
    assert(*p1 == 10);  // Проверяем разыменование через оператор *
}

// Тест на перемещение указателя
void test_move_ptr() {
    UnqPtr<int> p1(new int(20));  // Создаем указатель p1
    assert(p1.get() != nullptr);  // Указатель инициализирован
    
    UnqPtr<int> p2 = std::move(p1);  // Перемещаем p1 в p2
    assert(p1.get() == nullptr);  // p1 после перемещения должен быть nullptr
    assert(p2.get() != nullptr);  // p2 должен теперь управлять объектом
    assert(*p2 == 20);  // Проверяем разыменование
}

// Тест на операторы сравнения (==, !=, <, <=, >, >=)
void test_comparison_operators() {
    UnqPtr<int> p1(new int(30));  // Создаем указатели для сравнения
    UnqPtr<int> p2(new int(40));
    UnqPtr<int> p3 = std::move(p1);  // p3 берет указатель p1

    //assert(p3 != p2);  // p3 и p2 указывают на разные объекты
    assert(p3 < p2 || p2 > p3);  // Проверяем операторы < и >
    assert(p2 >= p3);  // Проверяем >=
    assert(!(p3 >= p2));  // Проверяем, что p3 не >= p2
}

/*// Тест на работу с массивами
void test_array_support() {
    UnqPtr<int[]> pArray = make_unique<int>(5);  // Создаем массив на 5 элементов
    for (int i = 0; i < 5; ++i) {
        pArray[i] = i;  // Инициализируем массив
    }
    for (int i = 0; i < 5; ++i) {
        assert(pArray[i] == i);  // Проверяем значения
    }
}*/

// Тест на метод release
void test_release() {
    UnqPtr<int> p1(new int(50));  // Создаем указатель p1
    int* raw_ptr = p1.realese();  // Освобождаем указатель

    assert(p1.get() == nullptr);  // После release, p1 должен стать nullptr
    assert(raw_ptr != nullptr);  // raw_ptr должен указывать на объект

    delete raw_ptr;  // Освобождаем память вручную
}

// Тест на метод reset
void test_reset() {
    UnqPtr<int> p1(new int(60));  // Создаем указатель p1
    assert(p1.get() != nullptr);  // Убедимся, что указатель не nullptr
    
    p1.reset();  // Сбрасываем указатель
    assert(p1.get() == nullptr);  // После reset, указатель должен быть nullptr
}

// Тест на проверку освобождения ресурса (метод IsFree)
void test_is_free() {
    UnqPtr<int> p1(new int(70));  // Создаем указатель p1
    assert(!p1.IsFree());  // Указатель не свободен
    
    p1.reset();  // Сбрасываем указатель
    assert(p1.IsFree());  // Теперь указатель должен быть свободен
}

