#ifndef LAB4_ADJACENTVERTEXITERATOR_H
#define LAB4_ADJACENTVERTEXITERATOR_H

#include "Edge.h"
#include "Vertex.h"
#include <iterator>
#include <type_traits>
#include <stdexcept>

template <typename T>
class AdjacentVertexIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Vertex<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = Vertex<T>*;
    using reference = Vertex<T>*;

    explicit AdjacentVertexIterator(Edge<T>* start = nullptr, Vertex<T>* owner = nullptr) : current(start), owner(owner) {}

    reference operator*() const {
        return current ? current->getTo() : nullptr;
    }
    pointer operator->() const {
        return current ? current->getTo() : nullptr;
    }

    AdjacentVertexIterator& operator++() {
        if (current) current = current->getNextOut();
        return *this;
    }

    AdjacentVertexIterator operator++(int) {
        AdjacentVertexIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    AdjacentVertexIterator& operator--() {
        if (!owner) return *this;
        if (!current) {
            current = owner->getFirstOut();
            Edge<T>* last = nullptr;
            while (current) {
                last = current;
                current = current->getNextOut();
            }
            current = last;
            return *this;
        }
        Edge<T>* tmp = owner->getFirstOut();
        Edge<T>* prev = nullptr;
        while (tmp != current) {
            prev = tmp;
            tmp = tmp->getNextOut();
        }
        current = prev;
        return *this;
    }

    AdjacentVertexIterator operator--(int) {
        AdjacentVertexIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const AdjacentVertexIterator& other) const {
        return current == other.current;
    }
    bool operator!=(const AdjacentVertexIterator& other) const {
        return current != other.current;
    }

private:
    Edge<T>* current;
    Vertex<T>* owner;
};

template <typename T>
class ConstAdjacentVertexIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = const Vertex<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = const Vertex<T>*;
    using reference = const Vertex<T>*;

    explicit ConstAdjacentVertexIterator(const Edge<T>* start = nullptr, Vertex<T>* owner = nullptr) : current(start), owner(owner) {}

    reference operator*() const {
        return current ? current->getTo() : nullptr;
    }
    pointer operator->() const {
        return current ? current->getTo() : nullptr;
    }

    ConstAdjacentVertexIterator& operator++() {
        if (current) current = current->getNextOut();
        return *this;
    }

    ConstAdjacentVertexIterator operator++(int) {
        ConstAdjacentVertexIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    ConstAdjacentVertexIterator& operator--() {
        if (!owner) return *this;
        if (!current) {
            current = owner->getFirstOut();
            const Edge<T>* last = nullptr;
            while (current) {
                last = current;
                current = current->getNextOut();
            }
            current = last;
            return *this;
        }
        Edge<T>* tmp = owner->getFirstOut();
        Edge<T>* prev = nullptr;
        while (tmp != current) {
            prev = tmp;
            tmp = tmp->getNextOut();
        }
        current = prev;
        return *this;
    }

    ConstAdjacentVertexIterator operator--(int) {
        AdjacentVertexIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const ConstAdjacentVertexIterator& other) const {
        return current == other.current;
    }
    bool operator!=(const ConstAdjacentVertexIterator& other) const {
        return current != other.current;
    }

private:
    const Edge<T>* current;
    Vertex<T>* owner;
};

template <typename T>
using ReverseAdjacentVertexIterator = std::reverse_iterator<AdjacentVertexIterator<T>>;
template <typename T>
using ConstReverseAdjacentVertexIterator = std::reverse_iterator<ConstAdjacentVertexIterator<T>>;

#endif //LAB4_ADJACENTVERTEXITERATOR_H
