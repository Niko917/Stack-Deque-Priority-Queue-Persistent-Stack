#include "tests.hpp"
#include "user.hpp"

int main() {
    test_persistent_stack();
    Stack_tests();
    Deque_tests();
    Queue_tests();
    Priority_Queue_tests();

    run();

    return 0;
}