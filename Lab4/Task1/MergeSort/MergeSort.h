#pragma once
#include <vector>
#include "Utils.h"

template <typename T>
void merge(std::vector<T>& data, size_t left, size_t mid, size_t right) {
    size_t leftPartSize = mid - left + 1;
    size_t rightPartSize = right - mid;

    std::vector <T> leftPart(leftPartSize), rightPart(rightPartSize);
    copySubVectors(data, leftPart, rightPart, left, mid, right);
    mergeSubVectors(data, leftPart, rightPart, left, right);
}

template <typename T>
void mergeSortImpl(std::vector<T>& data, size_t left, size_t right){
    if (left >= right)
        return;

    size_t mid = left + (right - left) / 2;
    mergeSortImpl(data, left, mid);
    mergeSortImpl(data, mid + 1, right);
    merge(data, left, mid, right);
}

template <typename T>
void merge(T* array, size_t left, size_t mid, size_t right){
    size_t leftPartSize = mid - left + 1;
    size_t rightPartSize = right - mid;


    T* leftPart = new T[leftPartSize];
    T* rightPart = new T[rightPartSize];

    copySubArrays(array, leftPart, rightPart, left, mid, right);
    mergeSubArrays(array, leftPart, rightPart, left, mid, right);

    delete[] leftPart;
    delete[] rightPart;
}

template <typename T>
void mergeSortImpl(T* array, size_t left, size_t right){
    if (left >= right)
        return;

    size_t mid = left + (right - left) / 2;
    mergeSortImpl(array, left, mid);
    mergeSortImpl(array, mid + 1, right);
    merge(array, left, mid, right);
}

template <typename T>
void mergeSort(std::vector<T>& data){
    if(!data.size())
        return;
    mergeSortImpl(data, 0, data.size() - 1);
}

template <typename T>
void mergeSort(T* array, size_t size){
    if(size == 0)
        return;
    mergeSortImpl(array, 0, size - 1);
}
