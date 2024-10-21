#include <iostream>
#include "TraitsForArrays.hpp"
#include "UnqPtr.hpp"
#include "ShrdPtr.hpp"
#include "UnqPtrTests.hpp"

int main(){
    test_create_and_dereference();
    test_move_ptr();
    test_comparison_operators();
    test_release();
    test_reset();
    test_is_free();
return 0;
}

