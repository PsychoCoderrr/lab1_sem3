#include "Ui.hpp"
#include "str_switch.hpp"
#include "UnqPtrTests.hpp"
#include "ShrdPtrTest.hpp"
#include "WeakPtrTest.hpp"
#include "DynamicArray.hpp"
#include "DynamicArrayTest.hpp"

void UiPrint()
{
    int flag = 1;
    std::string command;
    while(flag)
    {
        std::cout<< "Enter your command" << std::endl;
        std::cin >> command;
        SWITCH(command)
        {
            CASE("UnqTest"):
            {
                test_create_and_dereference();
                test_move_ptr();
                test_comparison_operators();
                test_release();
                test_reset();
                test_is_free();
                std::cout<< "All tests were passed" << std::endl;
                break;
            }
            CASE("ShrdTest"):
            {
                test_empty_shared_ptr();
                test_shared_ptr_with_object();
                test_shared_ptr_copy();
                test_shared_ptr_move();
                test_shared_ptr_reset();
                test_shared_ptr_use_count();
                test_shared_ptr_dereference();
                break;
            }
            CASE("WeakTest"):
            {
                test_empty_weak_ptr();
                test_weak_ptr_from_shared();
                test_weak_ptr_copy();
                test_weak_ptr_move();
                test_weak_ptr_assignment();
                test_weak_ptr_expired();
                break;
            }
            CASE("ArrayTest"):
            {
                test_empty_array();
                test_array_with_size();
                test_array_with_elements();
                test_get_method();
                test_set_method();
                test_index_operator();
                test_resize();
                test_exceptions();
                break;
            }
            CASE("Stop"):
            {
                flag = 0;
                break;
            }
        }
    }
}
