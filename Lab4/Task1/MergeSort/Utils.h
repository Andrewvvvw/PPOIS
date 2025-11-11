#pragma once
#include <vector>

template <typename T>
void copySubVectors(const std::vector<T>& data, std::vector<T>& leftPart, std::vector<T>& rightPart,
                   size_t left, size_t mid, size_t right) {
    
    for (size_t i = 0; i < leftPart.size(); ++i)
        leftPart[i] = data[left + i];
    
    for (size_t i = 0; i < rightPart.size(); ++i)
        rightPart[i] = data[mid + 1 + i];
}

template <typename T>
void mergeSubVectors(std::vector<T>& data, const std::vector<T>& leftPart, const std::vector<T>& rightPart,
                size_t left, size_t right) {
    
    size_t i = 0, j = 0, k = left;
    
    while (i < leftPart.size() && j < rightPart.size())
        data[k++] = (leftPart[i] <= rightPart[j]) ? leftPart[i++] : rightPart[j++];
    
    while (i < leftPart.size())
        data[k++] = leftPart[i++];
    
    while (j < rightPart.size()) 
        data[k++] = rightPart[j++];
}

template <typename T>
void copySubArrays(const T* array, T* leftPart, T* rightPart,
                    size_t left, size_t mid, size_t right) {

    size_t leftSize = mid - left + 1;
    size_t rightSize = right - mid;
    for (size_t i = 0; i < leftSize; ++i)
        leftPart[i] = array[left + i];
    for (size_t j = 0; j < rightSize; ++j)
        rightPart[j] = array[mid + 1 + j];
}

template <typename T>
void mergeSubArrays(T* array, const T* leftPart, const T* rightPart,
                     size_t left, size_t mid, size_t right) {

    size_t leftSize = mid - left + 1;
    size_t rightSize = right - mid;
    size_t i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize)
        array[k++] = (leftPart[i] <= rightPart[j]) ? leftPart[i++] : rightPart[j++];

    while (i < leftSize) array[k++] = leftPart[i++];
    while (j < rightSize) array[k++] = rightPart[j++];
}
