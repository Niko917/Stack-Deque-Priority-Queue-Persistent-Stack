#include "tests.hpp"
#include "/home/nikolay/projects/algo/labs/2/src/mutable_array.h"
#include "/home/nikolay/projects/algo/labs/2/src/exceptions.h"
#include "/home/nikolay/projects/algo/labs/2/src/Sequence.h"
#include "assert.h"
#include "Priority_Queue.hpp"
#include <iostream>


void Stack_tests() {
    Stack<int> stack;
    assert(stack.empty());
    assert(stack.size() == 0);


    Stack<int> stack_copy(stack);
    assert(stack_copy.empty());
    assert(stack_copy.size() == 0);

    
    Stack<int> stack_assign;
    stack_assign = stack;
    assert(stack_assign.empty());
    assert(stack_assign.size() == 0);

    
    stack.push(1);
    assert(!stack.empty());
    assert(stack.size() == 1);
    assert(stack.top() == 1);

    
    stack.pop();
    assert(stack.empty());
    assert(stack.size() == 0);

    
    try {
        stack.top();
        assert(false); 
    } catch (const SEQUENCE_EXCEPTION& e) {
        assert(e.what() == "this Stack is empty!");
    }

    
    try {
        stack.pop();
        assert(false);
    } catch (const SEQUENCE_EXCEPTION& e) {
        assert(e.what() == "this Stack is empty!");
    }

    
    stack.push(1);
    stack.push(2);
    assert(stack.size() == 2);
    assert(stack.top() == 2);

    
    Stack<int> reversed_stack = stack.reverse();
    assert(reversed_stack.size() == 2);
    assert(reversed_stack.top() == 1);

    
    Stack<int> other_stack;
    other_stack.push(3);
    other_stack.push(4);
    Stack<int> concatenated_stack = stack.concat(other_stack);
    assert(concatenated_stack.size() == 4);
    assert(concatenated_stack.top() == 3);

    

    stack.push(5);
    stack.push(7);
    // while (!stack.empty()) {
    //     std::cout << "stack top: " << stack.top() << std::endl;
    //     stack.pop();
    // }

    Stack<int> sub_stack = stack.substack(1, 2);
    assert(sub_stack.size() == 2);

    // while (!sub_stack.empty()) {
    //     std::cout << "subctack top: " << sub_stack.Get_last() << std::endl;
    //     sub_stack.Pop_back();
    // }

    stack.resize(5);
    assert(stack.size() == 5);

    std::cout << "All tests of stack passed!" << std::endl;
}


void Queue_tests() {

    Queue<std::string> q;
    assert(q.empty());
    assert(q.size() == 0);

    Queue<std::string> q_copy(q);
    assert(q_copy.empty());
    assert(q_copy.size() == 0);

    q.enqueue("Hi!");
    q.enqueue("My name is Nikolay!");
    assert(!q.empty());
    assert(q.size() == 2);

    q.dequeue();
    assert(q.size() == 1);
    assert(q.front() == "My name is Nikolay!"); 


        
    Queue<int> q_2;

    
    q_2.enqueue(1);
    q_2.enqueue(2);
    q_2.enqueue(3);
    q_2.enqueue(4);

    
    Queue<int> reversed_q = q_2.reverse();

    
    
    Queue<double> other_q;
    Queue<double> other_q_2;
    
    other_q.enqueue(2.3);
    other_q.enqueue(3.14);

    other_q_2.enqueue(45.6);


    Queue<double> concatenated_q = other_q_2.concat(other_q);
    assert(concatenated_q.size() == 3);
    
    // assert(concatenated_q.front() == 45.6);
    // concatenated_q.dequeue();
    // assert(concatenated_q.front() == 2.3);
    // concatenated_q.dequeue();
    // assert(concatenated_q.front() == 3.14);
    // concatenated_q.dequeue();

    Queue<double> sub_queue = concatenated_q.sub_queue(0, 1);
    
    assert(sub_queue.size() == 1);
    
    assert(sub_queue.front() == 45.6);

    std::cout << "All tests of queue passed!" << std::endl;
}


 void Deque_tests() {

    Deque<int> deque;
    assert(deque.empty());
    assert(deque.size() == 0);

    
    Deque<int> deque_copy(deque);
    assert(deque_copy.empty());
    assert(deque_copy.size() == 0);

    
    Deque<int> deque_assign;
    deque_assign = deque;
    assert(deque_assign.empty());
    assert(deque_assign.size() == 0);

    
    deque.push_front(1);
    assert(!deque.empty());
    assert(deque.size() == 1);
    assert(deque.front() == 1);
    assert(deque.back() == 1);

    
    deque.push_back(2);
    assert(deque.size() == 2);
    assert(deque.front() == 1);
    assert(deque.back() == 2);

    
    deque.pop_front();
    assert(deque.size() == 1);
    assert(deque.front() == 2);
    assert(deque.back() == 2);

    
    deque.pop_back();
    assert(deque.empty());
    assert(deque.size() == 0);

    
    deque.resize(5);
    assert(deque.size() == 5);

    
    deque.push_front(1);
    deque.push_back(2);

    // for (int i = deque.size(); i > 0; --i) {
    //     std::cout << deque.front() << " ";
    //     deque.pop_front();
    // }

    Deque<int> reversed_deque = deque.reverse();
    assert(reversed_deque.size() == 7);
    
    assert(reversed_deque.front() == 2);
    assert(reversed_deque.back() == 1);

    
    Deque<int> other_deque;
    other_deque.push_back(3);
    other_deque.push_back(4);

    Deque<int> other_deque_2;
    other_deque_2.push_front(7);
    other_deque_2.push_back(18);

    Deque<int> concatenated_deque = other_deque.concat(other_deque_2);
    assert(concatenated_deque.size() == 4);


    assert(concatenated_deque.front() == 3);
    assert(concatenated_deque.back() == 18);

    
    Deque<int> dq;

    
    for (int i = 0; i < 10; ++i) {
        dq.push_back(i);
    }

    
    Deque<int> subdeque = dq.subdeque(2, 5);
    
    assert(subdeque.size() == 3);
    assert(subdeque.front() == 2);
    assert(subdeque.back() == 4);

    
    Deque<int> subdeque_2 = dq.subdeque(5, 6);
    assert(subdeque_2.size() == 1);
    assert(subdeque_2.front() == 5);
    assert(subdeque_2.back() == 5);

    
    Deque<int> subdeque_3 = dq.subdeque(0, 10);
    assert(subdeque_3.size() == 10);
    assert(subdeque_3.front() == 0);
    assert(subdeque_3.back() == 9);

    
    try {
        subdeque = deque.subdeque(5, 15);
        assert(false);
    } catch (const SEQUENCE_EXCEPTION& e) {
        assert(e.error == ERRORS::Index_Out_of_range);
    }

    
    Deque<int> empty_deque;
    try {
        subdeque = empty_deque.subdeque(0, 1);
        assert(false);
    } catch (const SEQUENCE_EXCEPTION& e) {
        assert(e.error == ERRORS::Index_Out_of_range);
    }

    
    std::cout << "All tests of deque passed!" << std::endl;
}


void Priority_Queue_tests() {
    Priority_Queue<int> pq;

    
    pq.push(5, 10);
    pq.push(3, 20);
    pq.push(7, 5);

    assert(pq.extract_min() == 20);
    assert(pq.extract_min() == 10);
    assert(pq.extract_min() == 5);

    
    assert(pq.empty());

    
    Priority_Queue<int> pq1;
    pq1.push(1, 1);
    pq1.push(2, 2);

    Priority_Queue<int> pq2;
    pq2.push(3, 3);
    pq2.push(4, 4);

    pq1.Concat(pq2);
    assert(pq1.extract_min() == 1);
    assert(pq1.extract_min() == 2);
    assert(pq1.extract_min() == 3);
    assert(pq1.extract_min() == 4);

    
    pq.push(1, 1);
    pq.push(2, 2);
    pq.push(3, 3);
    pq.push(4, 4);

    std::vector<Priority_Node<int>> subqueue = pq.get_subqueue(1, 3);
    assert(subqueue.size() == 2);
    assert(subqueue[0].item == 2);
    assert(subqueue[1].item == 3);

    std::cout << "All tests for priority queue passed!" << std::endl;
}
