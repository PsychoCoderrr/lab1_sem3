#include <iostream>
#include "TraitsForArrays.hpp"
#include "UnqPtr.hpp"
#include "ShrdPtr.hpp"
#include "UnqPtrTests.hpp"
#include "ShrdPtrTest.hpp"

int main(){
    test_create_and_dereference();
    test_move_ptr();
    test_comparison_operators();
    test_release();
    test_reset();
    test_is_free();
    
    test_empty_shared_ptr();
    test_shared_ptr_with_object();
    test_shared_ptr_copy();
    test_shared_ptr_move();
    test_shared_ptr_reset();
    test_shared_ptr_use_count();
    test_shared_ptr_dereference();
return 0;
}

