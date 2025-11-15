#ifndef LAB4_VERTEXITERATOR_H
#define LAB4_VERTEXITERATOR_H

#include <map>
#include <memory>
#include <type_traits>
#include "Vertex.h"

template <typename T>
class Graph;

template <typename T>
class VertexIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Vertex<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = Vertex<T>**;
    using reference = Vertex<T>*&;

    VertexIterator(std::vector<Vertex<T>*>::iterator it) : iter(it) {}

    reference operator*() {
        return *iter;
    }
    pointer operator->() {
        return &(*iter);
    }

    VertexIterator& operator++() {
        ++iter; return *this;
    }
    VertexIterator operator++(int) {
        VertexIterator tmp = *this;
        ++iter;
        return tmp;
    }
    VertexIterator& operator--() {
        --iter;
        return *this;
    }
    VertexIterator operator--(int) {
        VertexIterator tmp = *this;
        --iter;
        return tmp;
    }

    bool operator==(const VertexIterator& other) const {
        return iter == other.iter;
    }
    bool operator!=(const VertexIterator& other) const {
        return iter != other.iter;
    }

private:
    typename std::vector<Vertex<T>*>::iterator iter;
};

template <typename T>
class ConstVertexIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const Vertex<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = const Vertex<T>**;
    using reference = const Vertex<T>*;

    ConstVertexIterator(typename std::vector<Vertex<T>*>::const_iterator it) : iter(it) {}

    reference operator*() {
        return *iter;
    }
    pointer operator->() {
        return &(*iter);
    }

    ConstVertexIterator& operator++() {
        ++iter;
        return *this;
    }
    ConstVertexIterator operator++(int) {
        ConstVertexIterator tmp = *this;
        ++iter;
        return tmp;
    }
    ConstVertexIterator& operator--() {
        --iter;
        return *this;
    }
    ConstVertexIterator operator--(int) {
        ConstVertexIterator tmp = *this;
        --iter;
        return tmp;
    }

    bool operator==(const ConstVertexIterator& other) const {
        return iter == other.iter;
    }
    bool operator!=(const ConstVertexIterator& other) const {
        return iter != other.iter;
    }

private:
    typename std::vector<Vertex<T>*>::const_iterator iter;
};

template <typename T>
using ReverseVertexIterator = std::reverse_iterator<VertexIterator<T>>;
template <typename T>
using ConstReverseVertexIterator = std::reverse_iterator<ConstVertexIterator<T>>;

#endif //LAB4_VERTEXITERATOR_H
