#pragma once

#include "/home/nikolay/projects/algo/labs/2/src/mutable_array.h"
#include "/home/nikolay/projects/algo/labs/2/src/exceptions.h"
#include "/home/nikolay/projects/algo/labs/2/src/Sequence.h"
#include <vector>


template <typename T>
class Binary_heap {
private:
    Mutable_Array_Sequence<T> data;

public:
    Binary_heap() = default;

    void sift_down(size_t index);

    void sift_up(size_t index);

    void insert(const T& item);

    T extract_min();

    bool empty() const;

    size_t size() const;

    const T& get_element(size_t index) const;

    void set_element(size_t index, const T& value);

    std::vector<T> get_elements() const;
};

template <typename T>
void Binary_heap<T>::sift_down(size_t index) {
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    size_t smallest = index;

    if (left < data.Get_length() && data[left] < data[smallest]) {
        smallest = left;
    }
    if (right < data.Get_length() && data[right] < data[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        std::swap(data[index], data[smallest]);
        sift_down(smallest);
    }
}

template <typename T>
void Binary_heap<T>::sift_up(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (data[index] >= data[parent]) {
            break;
        }
        std::swap(data[index], data[parent]);
        index = parent;
    }
}

template <typename T>
void Binary_heap<T>::insert(const T& item) {
    data.Append(item);
    sift_up(data.Get_length() - 1);
}

template <typename T>
T Binary_heap<T>::extract_min() {
    if (data.Get_length() == 0) {
        throw SEQUENCE_EXCEPTION{ERRORS::Queue_is_empty};
    }
    T min_item = data[0];
    data[0] = data[data.Get_length() - 1];
    data.Pop_back();
    if (!data.empty()) {
        sift_down(0);
    }
    return min_item;
}


template <typename T>
const T& Binary_heap<T>::get_element(size_t index) const {
    if (index >= this->data.Get_length()) {
        throw SEQUENCE_EXCEPTION{ERRORS::Index_Out_of_range};
    }
    return data[index];
}


template <typename T>
void Binary_heap<T>::set_element(size_t index, const T& value) {
    if (index >= this->data.Get_length()) {
        throw SEQUENCE_EXCEPTION{ERRORS::Index_Out_of_range};
    }
    data[index] = value;
}


template <typename T>
bool Binary_heap<T>::empty() const {
    return data.Get_length() == 0;
}

template <typename T>
size_t Binary_heap<T>::size() const {
    return data.Get_length();
}


template <typename T>
std::vector<T> Binary_heap<T>::get_elements() const {
    std::vector<T> elements;
    for (size_t i = 0; i < data.Get_length(); ++i) {
        elements.push_back(data[i]);
    }
    return elements;
}