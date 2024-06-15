#pragma once

#include "/home/nikolay/projects/algo/labs/2/src/mutable_array.h"
#include "/home/nikolay/projects/algo/labs/2/src/exceptions.h"
#include "/home/nikolay/projects/algo/labs/2/src/Sequence.h"


template <typename T>
class Stack {

private:
    Mutable_Array_Sequence<T> array;

public:
    Stack() : array() {}
    
    ~Stack() {
        array.clear();
    }

    Stack(Mutable_Array_Sequence<T>& arr) : array(arr) {}

    Stack(const Stack<T>& other_stack) : array(other_stack.array) {}

    T top() const;

    void pop();

    void push(const T& element);

    Stack<T> reverse();

    size_t size() const;

    Stack<T> concat(Stack<T>& other_stack);

    Stack<T> substack(size_t start_index, size_t end_index);


    bool empty() const;
    
    Stack<T>& operator=(const Stack<T>& other_stack);

    void resize(size_t new_size);

    void print_stack();

};


// ---------------------------------------------------------
template <typename T>
T Stack<T>::top() const {
    if (array.Get_length() == 0) {
        throw SEQUENCE_EXCEPTION{ERRORS::Stack_is_empty};
    }
    return array.Get_last();
}


template <typename T>
void Stack<T>::pop() {
    if (array.Get_length() == 0) {
        throw SEQUENCE_EXCEPTION{ERRORS::Stack_is_empty};
    }
    array.Pop_back();
}


template <typename T>
void Stack<T>::push(const T& element) {
    array.Append(element);
}


template <typename T>
Stack<T> Stack<T>::reverse() {
    Stack<T> reversed_stack;
    Stack<T> temp_stack = *this;
    while (!temp_stack.empty()) {
        reversed_stack.push(temp_stack.top());
        temp_stack.pop();
    }
    return reversed_stack;
}


template <typename T>
    size_t Stack<T>::size() const {
    return array.Get_length();
}


template <typename T>
Stack<T> Stack<T>::concat(Stack<T>& other_stack) {
    if (array.Get_length() == 0) {
        throw SEQUENCE_EXCEPTION{ERRORS::Stack_is_empty};
    }

    Stack<T> result = *this;
    while (!other_stack.empty()) {
        result.push(other_stack.top());
        other_stack.pop();
    }
    return result;
}


template <typename T>
Stack<T> Stack<T>::substack(size_t start_index, size_t end_index) {
    if (end_index > array.Get_length() || start_index > end_index) {
        throw SEQUENCE_EXCEPTION{ERRORS::Index_Out_of_range};
    }
    Stack<T> temp_stack;
    for (size_t i = start_index; i <= end_index; ++i) {
        temp_stack.push(array[i]);
    }
    return temp_stack;
}


template <typename T>
bool Stack<T>::empty() const {
    if (array.Get_length() == 0) {
        return true;
    }
    return false;
}


template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other_stack) {
    if (this != &other_stack) {
        array = other_stack.array;
    }
    return *this;
}


template <typename T>
void Stack<T>::resize(size_t new_size) {
    if (array.Get_length() == 0) {
        throw SEQUENCE_EXCEPTION{ERRORS::Stack_is_empty};
    }
    array.Resize(new_size);
}


template<typename T>
void Stack<T>::print_stack() {
    for (size_t i = 0; i < array.Get_length(); ++i) {
        std::cout << array[array.Get_length() - i - 1] << " ";
    }
    std::cout << std::endl;
}