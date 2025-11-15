#ifndef LAB4_INCIDENTEDGEITERATOR_H
#define LAB4_INCIDENTEDGEITERATOR_H

#include "Edge.h"
#include "Vertex.h"
#include <iterator>
#include <utility>
#include <type_traits>

template <typename T>
class IncidentEdgeIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Edge<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = Edge<T>**;
    using reference = Edge<T>*&;

    IncidentEdgeIterator(Vertex<T>* vertex, bool outgoing)
            : current(outgoing ? vertex->getFirstOut() : vertex->getFirstIn()), outgoing(outgoing), vertex(vertex), prev(nullptr) {}

    reference operator*() {
        if (!current) throw std::out_of_range("Dereferencing end iterator");
        return current;
    }
    pointer operator->() {
        if (!current) throw std::out_of_range("Dereferencing end iterator");
        return &current;
    }

    IncidentEdgeIterator& operator++() {
        if (!current) return *this;
        prev = current;
        current = outgoing ? current->getNextOut() : current->getNextIn();
        return *this;
    }

    IncidentEdgeIterator operator++(int) {
        IncidentEdgeIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    IncidentEdgeIterator& operator--() {
        if (!vertex) return *this;
        if (!prev) {
            current = outgoing ? vertex->getFirstOut() : vertex->getFirstIn();
            prev = nullptr;
            Edge<T>* last = nullptr;
            while (current) {
                last = current;
                current = outgoing ? current->getNextOut() : current->getNextIn();
            }
            current = last;
            return *this;
        }
        Edge<T>* tmp = outgoing ? vertex->getFirstOut() : vertex->getFirstIn();
        Edge<T>* last = nullptr;
        while (tmp != current) {
            last = tmp;
            tmp = outgoing ? tmp->getNextOut() : tmp->getNextIn();
        }
        current = last;
        return *this;
    }

    IncidentEdgeIterator operator--(int) {
        IncidentEdgeIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const IncidentEdgeIterator& other) const {
        return current == other.current;
    }
    bool operator!=(const IncidentEdgeIterator& other) const {
        return current != other.current;
    }

private:
    Edge<T>* current;
    bool outgoing;
    Vertex<T>* vertex;
    Edge<T>* prev;
};

template <typename T>
class ConstIncidentEdgeIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = const Edge<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = const Edge<T>**;
    using reference = const Edge<T>*&;

    ConstIncidentEdgeIterator(const Vertex<T>* vertex, bool outgoing)
            : current(outgoing ? vertex->getFirstOut() : vertex->getFirstIn()), outgoing(outgoing), vertex(vertex), prev(nullptr) {}

    reference operator*() {
        if (!current) throw std::out_of_range("Dereferencing end iterator");
        return current;
    }
    pointer operator->() {
        if (!current) throw std::out_of_range("Dereferencing end iterator");
        return &current;
    }

    ConstIncidentEdgeIterator& operator++() {
        if (current) current = outgoing ? current->getNextOut() : current->getNextIn();
        return *this;
    }

    ConstIncidentEdgeIterator operator++(int) {
        ConstIncidentEdgeIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    ConstIncidentEdgeIterator& operator--() {
        if (!vertex) return *this;
        if (!prev) {
            current = outgoing ? vertex->getFirstOut() : vertex->getFirstIn();
            prev = nullptr;
            Edge<T>* last = nullptr;
            while (current) {
                last = current;
                current = outgoing ? current->getNextOut() : current->getNextIn();
            }
            current = last;
            return *this;
        }
        Edge<T>* tmp = outgoing ? vertex->getFirstOut() : vertex->getFirstIn();
        Edge<T>* last = nullptr;
        while (tmp != current) {
            last = tmp;
            tmp = outgoing ? tmp->getNextOut() : tmp->getNextIn();
        }
        current = last;
        return *this;
    }

    ConstIncidentEdgeIterator operator--(int) {
        IncidentEdgeIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const ConstIncidentEdgeIterator& other) const {
        return current == other.current;
    }
    bool operator!=(const ConstIncidentEdgeIterator& other) const {
        return current != other.current;
    }


private:
    const Edge<T>* current;
    bool outgoing;
    Vertex<T>* vertex;
    Edge<T>* prev;
};

template <typename T>
using ReverseIncidentEdgeIterator = std::reverse_iterator<IncidentEdgeIterator<T>>;
template <typename T>
using ConstReverseIncidentEdgeIterator = std::reverse_iterator<ConstIncidentEdgeIterator<T>>;

#endif //LAB4_INCIDENTEDGEITERATOR_H
