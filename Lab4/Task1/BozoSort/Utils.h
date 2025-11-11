#pragma once
#include <vector>

template <typename T>
bool isVectorSorted(std::vector<T>& data) {
    for(size_t index = 0; index < data.size() - 1; index++) {
        if(data[index] > data[index + 1])
            return false;
    }
    return true;
}

template <typename T>
bool isArraySorted(T* array, size_t size) {
    for(size_t index = 0; index < size - 1; index++) {
        if(array[index] > array[index + 1])
            return false;
    }
    return true;
}

