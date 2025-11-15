#ifndef LAB4_EDGEITERATOR_H
#define LAB4_EDGEITERATOR_H

#include "Vertex.h"
#include "Edge.h"

template <typename T>
class Graph;

template <typename T>
class EdgeIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Edge<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = Edge<T>**;
    using reference = Edge<T>*&;

    EdgeIterator(typename std::vector<Edge<T>*>::iterator it) : iter(it) {}

    reference operator*() {
        return *iter;
    }
    pointer operator->() {
        return &(*iter);
    }

    EdgeIterator& operator++() {
        ++iter;
        return *this;
    }
    EdgeIterator operator++(int) {
        EdgeIterator tmp = *this;
        ++iter; return tmp;
    }
    EdgeIterator& operator--() {
        --iter;
        return *this;
    }
    EdgeIterator operator--(int) {
        EdgeIterator tmp = *this;
        --iter;
        return tmp;
    }

    bool operator==(const EdgeIterator& other) const {
        return iter == other.iter;
    }
    bool operator!=(const EdgeIterator& other) const {
        return iter != other.iter;
    }

private:
    typename std::vector<Edge<T>*>::iterator iter;
};

template <typename T>
class ConstEdgeIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const Edge<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = const Edge<T>**;
    using reference = const Edge<T>*&;

    ConstEdgeIterator(typename std::vector<Edge<T>*>::const_iterator it) : iter(it) {}

    reference operator*() {
        return *iter;
    }
    pointer operator->() {
        return &(*iter);
    }

    ConstEdgeIterator& operator++() {
        ++iter; return *this;
    }
    ConstEdgeIterator operator++(int) {
        ConstEdgeIterator tmp = *this;
        ++iter;
        return tmp;
    }
    ConstEdgeIterator& operator--() {
        --iter;
        return *this;
    }
    ConstEdgeIterator operator--(int) {
        ConstEdgeIterator tmp = *this;
        --iter;
        return tmp;
    }

    bool operator==(const ConstEdgeIterator& other) const {
        return iter == other.iter;
    }
    bool operator!=(const ConstEdgeIterator& other) const {
        return iter != other.iter;
    }

private:
    typename std::vector<Edge<T>*>::const_iterator iter;
};

template <typename T>
using ReverseEdgeIterator = std::reverse_iterator<EdgeIterator<T>>;
template <typename T>
using ConstReverseEdgeIterator = std::reverse_iterator<ConstEdgeIterator<T>>;

#endif
