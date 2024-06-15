#pragma once

#include "/home/nikolay/projects/algo/labs/2/src/mutable_array.h"
#include "/home/nikolay/projects/algo/labs/2/src/exceptions.h"
#include "/home/nikolay/projects/algo/labs/2/src/Sequence.h"
#include "Binary_heap.hpp"
#include <vector>

template <typename T>
class Priority_Node {
public:
    long priority;
    T item;

    Priority_Node() : priority(0), item(T()) {}
    Priority_Node(const long priority, const T& value) : priority(priority), item(value) {}
    Priority_Node(const Priority_Node& other_Node) : priority(other_Node.priority), item(other_Node.item) {}
    ~Priority_Node() = default;

    void change_priority(const long new_priority);
    void change_value(const T& new_value);

    bool operator > (const Priority_Node& node) const;
    bool operator >= (const Priority_Node& node) const;
    bool operator < (const Priority_Node& node) const;
    bool operator <= (const Priority_Node& node) const;
    bool operator == (const Priority_Node& node) const;
};


template <typename T>
void Priority_Node<T>::change_priority(const long new_priority) {
    this->priority = new_priority;
}


template <typename T>
void Priority_Node<T>::change_value(const T& new_value) {
    this->item = new_value;
}


template <typename T>
bool Priority_Node<T>::operator>(const Priority_Node& node) const {
    return this->priority > node.priority;
}


template <typename T>
bool Priority_Node<T>::operator>=(const Priority_Node& node) const {
    return this->priority >= node.priority;
}


template <typename T>
bool Priority_Node<T>::operator<(const Priority_Node& node) const {
    return this->priority < node.priority;
}


template <typename T>
bool Priority_Node<T>::operator<=(const Priority_Node& node) const {
    return this->priority <= node.priority;
}


template <typename T>
bool Priority_Node<T>::operator==(const Priority_Node& node) const {
    return this->priority == node.priority;
}


// ----------------------------------------------------------------------------------


template <typename T>
class Priority_Queue {
private:
    Binary_heap<Priority_Node<T>> queue;

public:
    Priority_Queue() = default;

    void push(const long priority, const T& item);
    
    T extract_min();
    
    void Concat(const Priority_Queue<T>& other_q);
    
    std::vector<Priority_Node<T>> get_subqueue(size_t start_index, size_t end_index);
    
    void change_priority(const long old_priority, const long new_priority);
    
    bool empty() const;
    
    size_t size() const;

    void print_Priority_Queue();
};


template <typename T>
size_t Priority_Queue<T>::size() const {
    return this->queue.size();
}


template <typename T>
void Priority_Queue<T>::push(const long priority, const T& item) {
    this->queue.insert(Priority_Node<T>(priority, item));
}


template <typename T>
T Priority_Queue<T>::extract_min() {
    return this->queue.extract_min().item;
}


template <typename T>
void Priority_Queue<T>::Concat(const Priority_Queue<T>& other_q) {
    for (size_t i = 0; i < other_q.queue.size(); ++i) {
        this->queue.insert(other_q.queue.get_element(i));
    }
}


template <typename T>
std::vector<Priority_Node<T>> Priority_Queue<T>::get_subqueue(size_t start_index, size_t end_index) {
    std::vector<Priority_Node<T>> result;
    if (start_index < queue.size() && end_index <= queue.size() && start_index <= end_index) {
        for (size_t i = start_index; i < end_index; ++i) {
            result.push_back(queue.get_element(i));
        }
    }
    return result;
}


template <typename T>
bool Priority_Queue<T>::empty() const {
    return this->queue.empty();
}


template<typename T>
void Priority_Queue<T>::print_Priority_Queue() {
    
    std::vector<Priority_Node<T>> elements = queue.get_elements();
    for (const auto& elem : elements) {
        std::cout << elem.item << " ";
    }
    std::cout << std::endl;
}