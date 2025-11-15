#ifndef LAB4_EDGE_H
#define LAB4_EDGE_H

#include "Vertex.h"

template <typename T>
class Edge {
public:
    Edge(Vertex<T>* from, Vertex<T>* to) : fromVertex(from), toVertex(to) {}

    Vertex<T>* getFrom() const {
        return fromVertex;
    }
    Vertex<T>* getTo() const {
        return toVertex;
    }

    Edge* getNextOut() const {
        return nextOut;
    }
    void setNextOut(Edge* e) {
        nextOut = e;
    }

    Edge* getNextIn() const {
        return nextIn;
    }
    void setNextIn(Edge* e) {
        nextIn = e;
    }

private:
    Vertex<T>* fromVertex;
    Vertex<T>* toVertex;
    Edge* nextOut = nullptr;
    Edge* nextIn = nullptr;

};

#endif //LAB4_EDGE_H
