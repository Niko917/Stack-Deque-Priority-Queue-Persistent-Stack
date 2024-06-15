#pragma once

#include "/home/nikolay/projects/algo/labs/2/src/mutable_list.h"
#include "/home/nikolay/projects/algo/labs/2/src/exceptions.h"
#include "/home/nikolay/projects/algo/labs/2/src/Sequence.h"

template <typename T>
class Deque {
private:
    

public:

    Mutable_List_Sequence<T> list;

    Deque() : list() {}

    ~Deque() {
        list.clear();
    }

    Deque(Mutable_List_Sequence<T>& list) : list(list) {}

    Deque(const Deque<T>& other_deque);

    // ----------------------------------------------------------

    T front() const;

    T back() const;

    void push_front(const T& item);

    void push_back(const T& item);

    void pop_front();

    void pop_back();

    size_t size() const;

    bool empty() const;

    Deque<T> operator=(const Deque<T>& other_deque);

    void resize(size_t new_size);

    Deque<T> concat(const Deque<T>& other_deque);

    Deque<T> subdeque(size_t start_index, size_t end_index);

    Deque<T> reverse();

    void print_Deque();

};

    // -----------------------------------------------------------

template <typename T>
Deque<T>::Deque(const Deque<T>& other_deque) : Deque<T>() {
    List_Sequence<T>* seq = new Mutable_List_Sequence<T>();
    for (size_t i = 0; i < other_deque.list.Get_length(); ++i) {
        seq->Append(other_deque.list.Get(i));
    }
    for (size_t i = 0; i < seq->Get_length(); ++i) {
        this->push_back((*seq).Get(i));
    }
}


template <typename T>
T Deque<T>::front() const {
    if (list.Get_length() == 0) {
        throw SEQUENCE_EXCEPTION{ERRORS::Deque_is_empty};
    }
    return list.Get_first();
}


template <typename T>
T Deque<T>::back() const {
    if (list.Get_length() == 0) {
        throw SEQUENCE_EXCEPTION{ERRORS::Deque_is_empty};
    }
    return list.Get_last();
}


template <typename T>
void Deque<T>::push_front(const T& item) {
    list.Prepend(item);
}


template <typename T>
void Deque<T>::push_back(const T& item) {
        list.Append(item);
}


template <typename T>
void Deque<T>::pop_front() {
    if (list.Get_length() == 0) {
        throw SEQUENCE_EXCEPTION{ERRORS::Deque_is_empty};
    }
    list.Pop_front();
}


template <typename T>
void Deque<T>::pop_back() {
    if (list.Get_length() == 0) {
        throw SEQUENCE_EXCEPTION{ERRORS::Deque_is_empty};
    }
    list.Pop_back();
}


template <typename T>
size_t Deque<T>::size() const {
    return list.Get_length();
}


template <typename T>
bool Deque<T>::empty() const {
    return list.Get_length() == 0;
}


template <typename T>
Deque<T> Deque<T>::operator=(const Deque<T>& other_deque) {
    if (this != &other_deque) {
        list = other_deque.list;
    }
    return *this;
}


template <typename T>
void Deque<T>::resize(size_t new_size) {
    list.Resize(new_size);
}



template <typename T>
Deque<T> Deque<T>::concat(const Deque<T>& other_deque) {
    Deque<T> concatenation = *this;
    for (size_t i = 0; i < other_deque.size(); ++i) {
        concatenation.push_back(other_deque.list.Get(i));
    }
    return concatenation;
}


template <typename T>
Deque<T> Deque<T>::subdeque(size_t start_index, size_t end_index) {
    if (start_index < 0 || end_index > list.Get_length() || start_index > end_index) {
        throw SEQUENCE_EXCEPTION{ERRORS::Index_Out_of_range};
    }

    Deque<T> subdeque;
    for (int i = start_index; i < end_index; ++i) {
        subdeque.push_back(list[i]);
    }
    return subdeque;
}



template <typename T>
Deque<T> Deque<T>::reverse() {
    Deque<T> reversed_deque;

    for (size_t i = 0; i < list.Get_length(); ++i) {
        reversed_deque.push_front(list.Get(i));
    }

    return reversed_deque;
}


template<typename T>
void Deque<T>::print_Deque() {
    for (size_t i = 0; i < list.Get_length(); ++i) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
}


