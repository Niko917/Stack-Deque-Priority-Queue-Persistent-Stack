#include "Persistent.hpp"
#include <cassert>
#include <iostream>

void test_persistent_stack() {
    Persistent_Stack<int> stack;

    auto new_version = Persistent_Stack<int>(2178127, stack);

    assert(stack.empty());
    assert(stack.size() == 0);

    // first version
    auto stack_1 = stack.push(2);
    assert(!stack_1.empty());
    assert(stack_1.size() == 1);
    assert(stack_1.top() == 2);

    // second version
    auto stack_2 = stack_1.push(3);
    assert(!stack_2.empty());
    assert(stack_2.size() == 2);
    assert(stack_2.top() == 3);

    
    assert(stack_1.size() == 1);
    assert(stack_1.top() == 2);

    
    auto stack_1_pop = stack_1.pop();
    assert(stack_1_pop.empty());
    assert(stack_1_pop.size() == 0);

    
    assert(stack_2.size() == 2);
    assert(stack_2.top() == 3);

    // try {
    //     stack.pop();
    //     assert(false);
    // } catch (const SEQUENCE_EXCEPTION& e) {
    //     std::cout << "the error is: " << e.what() << std::endl;
    // }

    // try {
    //     stack.top();
    //     assert(false);
    // } catch (const SEQUENCE_EXCEPTION& e) {
    //     std::cout << "the error is: " << e.what() << std::endl;
    // }

    auto stack_3 = stack.push(5);
    auto elements = stack_3.get_elements();

    assert(elements.size() == 1);
    assert(elements[0] == 5);

    // for (int i = 0; i < elements.size(); ++i) {
    //     std::cout << elements[i] << " ";
    // }
    // std::cout << "\n";
}


