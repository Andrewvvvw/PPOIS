#ifndef LAB4_BOZOSORT_H
#define LAB4_BOZOSORT_H
#include <vector>
#include <ctime>
#include "Utils.h"


template <typename T>
void bozoSort(std::vector<T>& data){
    if(!data.size())
        return;

    srand(time(NULL));
    while(!isVectorSorted(data)) {
        size_t index1 = rand() % data.size();
        size_t index2 = rand() % data.size();

        std::swap(data[index1], data[index2]);
    }
}

template <typename T>
void bozoSort(T* array, size_t size){
    if(size == 0)
        return;

    srand(time(NULL));
    while(!isArraySorted(array, size)) {
        size_t index1 = rand() % size;
        size_t index2 = rand() % size;

        std::swap(array[index1], array[index2]);
    }
}

#endif //LAB4_BOZOSORT_H
