#include "UnqPtr.hpp"
#include "MyDeleter.hpp"
#include <stdio.h>

template<typename T, typename Ptr_Deleter = Deleter<T>>
class UnqPtr
{
private:
    using element_type = T;
    using pointer = element_type*;
    using deleter_type = Ptr_Deleter;
    
public:
    
};
