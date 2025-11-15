#ifndef LAB4_GRAPHIMPLEMENTATION_H
#define LAB4_GRAPHIMPLEMENTATION_H

#include <algorithm>
#include <iostream>

template <typename T>
Graph<T>::Graph() : vertices(), edges() {}

template <typename T>
Graph<T>::~Graph() {
    clear();
}

template <typename T>
Graph<T>::Graph(const Graph<T>& other) {
    for (auto v : other.vertices) {
        vertices.push_back(new Vertex<T>(v->getValue()));
    }

    for (auto e : other.edges) {
        auto fromIt = std::find(other.vertices.begin(), other.vertices.end(), e->getFrom());
        auto toIt = std::find(other.vertices.begin(), other.vertices.end(), e->getTo());
        if (fromIt == other.vertices.end() || toIt == other.vertices.end()) continue;
        Vertex<T>* newFrom = vertices[std::distance(other.vertices.begin(), fromIt)];
        Vertex<T>* newTo = vertices[std::distance(other.vertices.begin(), toIt)];
        addEdge(newFrom, newTo);
    }
}

template <typename T>
bool Graph<T>::empty() const {
    return vertices.empty();
}

template <typename T>
void Graph<T>::clear() {
    for (auto e : edges) delete e;
    edges.clear();
    for (auto v : vertices) delete v;
    vertices.clear();
}

template <typename T>
Vertex<T>* Graph<T>::getVertex(size_type index) const {
    return vertices.at(index);
}

template <typename T>
std::size_t Graph<T>::vertexCount() const {
    return vertices.size();
}

template <typename T>
std::size_t Graph<T>::edgeCount() const {
    return edges.size();
}

template <typename T>
Vertex<T>* Graph<T>::addVertex(const T& value) {
    Vertex<T>* v = new Vertex<T>(value);
    vertices.push_back(v);
    return v;
}

template <typename T>
Edge<T>* Graph<T>::addEdge(Vertex<T>* from, Vertex<T>* to) {
    Edge<T>* e = new Edge<T>(from, to);
    edges.push_back(e);

    e->setNextOut(from->getFirstOut());
    from->setFirstOut(e);

    e->setNextIn(to->getFirstIn());
    to->setFirstIn(e);

    return e;
}

template <typename T>
Edge<T>* Graph<T>::addEdge(size_type fromIndex, size_type toIndex) {
    return addEdge(vertices.at(fromIndex), vertices.at(toIndex));
}

template <typename T>
bool Graph<T>::containsVertex(const Vertex<T>* v) const {
    return std::find(vertices.cbegin(), vertices.cend(), v) != vertices.cend();
}

template <typename T>
bool Graph<T>::containsEdge(const Vertex<T>* from, const Vertex<T>* to) const {
    for (Edge<T>* e = from->getFirstOut(); e != nullptr; e = e->getNextOut()) {
        if (e->getTo() == to) return true;
    }
    return false;
}

template <typename T>
std::size_t Graph<T>::outDegree(const Vertex<T>* v) const {
    std::size_t count = 0;
    for (Edge<T>* e = v->getFirstOut(); e != nullptr; e = e->getNextOut()) {
        ++count;
    }
    return count;
}


template <typename T>
std::size_t Graph<T>::inDegree(const Vertex<T>* v) const {
    std::size_t count = 0;
    for (Edge<T>* e = v->getFirstIn(); e != nullptr; e = e->getNextIn()) {
        ++count;
    }
    return count;
}

template <typename T>
std::size_t Graph<T>::vertexDegree(const Vertex<T> *v) const {
    return outDegree(v) + inDegree(v) - 2;
}

template <typename T>
std::size_t Graph<T>::edgeDegree(const Edge<T>* e) const {
    return outDegree(e->getFrom()) + inDegree(e->getTo());
}

template <typename T>
bool Graph<T>::removeVertex(Vertex<T>* v) {
    if (!containsVertex(v)) return false;

    Edge<T>* e = v->getFirstOut();
    while (e) {
        Edge<T>* next = e->getNextOut();
        removeEdge(e);
        e = next;
    }
    e = v->getFirstIn();
    while (e) {
        Edge<T>* next = e->getNextIn();
        removeEdge(e);
        e = next;
    }

    vertices.erase(std::remove(vertices.begin(), vertices.end(), v), vertices.end());
    delete v;
    return true;
}

template <typename T>
bool Graph<T>::removeEdge(Edge<T>* e) {
    if (!e) return false;

    Vertex<T>* from = e->getFrom();
    Vertex<T>* to = e->getTo();

    Edge<T>* prev = nullptr;
    Edge<T>* curr = from->getFirstOut();
    while (curr && curr != e) {
        prev = curr;
        curr = curr->getNextOut();
    }
    if (curr == e) {
        if (prev) prev->setNextOut(curr->getNextOut());
        else from->setFirstOut(curr->getNextOut());
    }

    prev = nullptr;
    curr = to->getFirstIn();
    while (curr && curr != e) {
        prev = curr;
        curr = curr->getNextIn();
    }
    if (curr == e) {
        if (prev) prev->setNextIn(curr->getNextIn());
        else to->setFirstIn(curr->getNextIn());
    }

    edges.erase(std::remove(edges.begin(), edges.end(), e), edges.end());
    delete e;
    return true;
}

template <typename T>
typename Graph<T>::vertex_iterator Graph<T>::verticesBegin() {
    return vertex_iterator(vertices.begin());
}

template <typename T>
typename Graph<T>::vertex_iterator Graph<T>::verticesEnd() {
    return vertex_iterator(vertices.end());
}

template <typename T>
typename Graph<T>::const_vertex_iterator Graph<T>::verticesCBegin() const {
    return const_vertex_iterator(vertices.cbegin());
}

template <typename T>
typename Graph<T>::const_vertex_iterator Graph<T>::verticesCEnd() const {
    return const_vertex_iterator(vertices.cend());
}

template <typename T>
typename Graph<T>::reverse_vertex_iterator Graph<T>::verticesRBegin() {
    return reverse_vertex_iterator(vertices.end());
}

template <typename T>
typename Graph<T>::reverse_vertex_iterator Graph<T>::verticesREnd() {
    return reverse_vertex_iterator(vertices.begin());
}

template <typename T>
typename Graph<T>::const_reverse_vertex_iterator Graph<T>::verticesCRBegin() const {
    return const_reverse_vertex_iterator(vertices.cend());
}

template <typename T>
typename Graph<T>::const_reverse_vertex_iterator Graph<T>::verticesCREnd() const {
    return const_reverse_vertex_iterator(vertices.cbegin());
}

template <typename T>
typename Graph<T>::edge_iterator Graph<T>::edgesBegin() {
    return edge_iterator(edges.begin());
}

template <typename T>
typename Graph<T>::edge_iterator Graph<T>::edgesEnd() {
    return edge_iterator(edges.end());
}

template <typename T>
typename Graph<T>::const_edge_iterator Graph<T>::edgesCBegin() const {
    return const_edge_iterator(edges.cbegin());
}

template <typename T>
typename Graph<T>::const_edge_iterator Graph<T>::edgesCEnd() const {
    return const_edge_iterator(edges.cend());
}

template <typename T>
typename Graph<T>::reverse_edge_iterator Graph<T>::edgesRBegin() {
    return reverse_edge_iterator(edges.end());
}

template <typename T>
typename Graph<T>::reverse_edge_iterator Graph<T>::edgesREnd() {
    return reverse_edge_iterator(edges.begin());
}

template <typename T>
typename Graph<T>::const_reverse_edge_iterator Graph<T>::edgesCRBegin() const {
    return const_reverse_edge_iterator(edges.cend());
}

template <typename T>
typename Graph<T>::const_reverse_edge_iterator Graph<T>::edgesCREnd() const {
    return const_reverse_edge_iterator(edges.cbegin());
}

template <typename T>
typename Graph<T>::incident_edge_iterator
Graph<T>::incidentEdgesBegin(Vertex<T>* v, bool outgoing) {
    return incident_edge_iterator(v, outgoing);
}

template <typename T>
typename Graph<T>::incident_edge_iterator
Graph<T>::incidentEdgesEnd(Vertex<T>* , bool ) {
    return incident_edge_iterator(nullptr, true);
}

template <typename T>
typename Graph<T>::const_incident_edge_iterator
Graph<T>::incidentEdgesCBegin(const Vertex<T>* v, bool outgoing) const {
    return const_incident_edge_iterator(const_cast<Vertex<T>*>(v), outgoing);
}

template <typename T>
typename Graph<T>::const_incident_edge_iterator
Graph<T>::incidentEdgesCEnd(const Vertex<T>* /*v*/, bool /*outgoing*/) const {
    return const_incident_edge_iterator(nullptr, true);
}

template <typename T>
typename Graph<T>::reverse_incident_edge_iterator
Graph<T>::incidentEdgesRBegin(Vertex<T>* v, bool outgoing) {
    return reverse_incident_edge_iterator(incidentEdgesEnd(v, outgoing));
}

template <typename T>
typename Graph<T>::reverse_incident_edge_iterator
Graph<T>::incidentEdgesREnd(Vertex<T>* v, bool outgoing) {
    return reverse_incident_edge_iterator(incidentEdgesBegin(v, outgoing));
}

template <typename T>
typename Graph<T>::const_reverse_incident_edge_iterator
Graph<T>::incidentEdgesCRBegin(const Vertex<T>* v, bool outgoing) const {
    return const_reverse_incident_edge_iterator(incidentEdgesCEnd(v, outgoing));
}

template <typename T>
typename Graph<T>::const_reverse_incident_edge_iterator
Graph<T>::incidentEdgesCREnd(const Vertex<T>* v, bool outgoing) const {
    return const_reverse_incident_edge_iterator(incidentEdgesCBegin(v, outgoing));
}

template <typename T>
typename Graph<T>::adjacent_vertex_iterator
Graph<T>::adjacentBegin(Vertex<T>* v) {
    return AdjacentVertexIterator<T>(v ? v->getFirstOut() : nullptr);
}

template <typename T>
typename Graph<T>::adjacent_vertex_iterator
Graph<T>::adjacentEnd(Vertex<T>* /*v*/) {
    return AdjacentVertexIterator<T>(nullptr);
}

template <typename T>
typename Graph<T>::const_adjacent_vertex_iterator
Graph<T>::adjacentCBegin(const Vertex<T>* v) const {
    return ConstAdjacentVertexIterator<T>(v ? v->getFirstOut() : nullptr);
}

template <typename T>
typename Graph<T>::const_adjacent_vertex_iterator
Graph<T>::adjacentCEnd(const Vertex<T>* /*v*/) const {
    return ConstAdjacentVertexIterator<T>(nullptr);
}

template <typename T>
typename Graph<T>::reverse_adjacent_vertex_iterator
Graph<T>::adjacentRBegin(Vertex<T>* v) {
    return reverse_adjacent_vertex_iterator(adjacentEnd(v));
}

template <typename T>
typename Graph<T>::reverse_adjacent_vertex_iterator
Graph<T>::adjacentREnd(Vertex<T>* v) {
    return reverse_adjacent_vertex_iterator(adjacentBegin(v));
}

template <typename T>
typename Graph<T>::const_reverse_adjacent_vertex_iterator
Graph<T>::adjacentCRBegin(const Vertex<T>* v) const {
    return const_reverse_adjacent_vertex_iterator(adjacentCEnd(v));
}

template <typename T>
typename Graph<T>::const_reverse_adjacent_vertex_iterator
Graph<T>::adjacentCREnd(const Vertex<T>* v) const {
    return const_reverse_adjacent_vertex_iterator(adjacentCBegin(v));
}

template <typename T>
bool Graph<T>::removeVertex(vertex_iterator it) {
    if (it == verticesEnd()) return false;
    return removeVertex(*it);
}

template <typename T>
bool Graph<T>::removeVertex(const_vertex_iterator it) {
    if (it == verticesCEnd()) return false;
    return removeVertex(*it);
}

template <typename T>
bool Graph<T>::removeEdge(edge_iterator it) {
    if (it == edgesEnd()) return false;
    return removeEdge(*it);
}

template <typename T>
bool Graph<T>::removeEdge(const_edge_iterator it) {
    if (it == edgesCEnd()) return false;
    return removeEdge(*it);
}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& other) {
    if (this == &other) return *this;
    clear();

    for (auto v : other.vertices) {
        vertices.push_back(new Vertex<T>(v->getValue()));
    }

    for (auto e : other.edges) {
        auto fromIt = std::find(other.vertices.begin(), other.vertices.end(), e->getFrom());
        auto toIt = std::find(other.vertices.begin(), other.vertices.end(), e->getTo());
        if (fromIt == other.vertices.end() || toIt == other.vertices.end()) continue;
        addEdge(vertices[std::distance(other.vertices.begin(), fromIt)],
                vertices[std::distance(other.vertices.begin(), toIt)]);
    }

    return *this;
}

template <typename T>
bool Graph<T>::checkVerticesEquality(std::vector<Vertex<T>*> verticesFirstGraph, std::vector<Vertex<T>*> verticesSecondGraph) {
    for (auto firstGraphVertex : verticesFirstGraph) {
        bool found = false;
        for (auto secondGraphVertex : verticesSecondGraph) {
            if (firstGraphVertex->getValue() == secondGraphVertex->getValue()) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }

}

template <typename T>
bool Graph<T>::checkEdgesEquality(std::vector<Edge<T> *> edgesFirstGraph, std::vector<Edge<T> *> edgesSecondGraph) {
    for (auto edge1 : edgesFirstGraph) {
        Vertex<T>* from = edge1->getFrom();
        Vertex<T>* to = edge1->getTo();
        bool found = false;
        for (auto edge2 : edgesSecondGraph) {
            if (from->getValue() == edge2->getFrom()->getValue() &&
                to->getValue() == edge2->getTo()->getValue()) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
}

template <typename T>
bool Graph<T>::operator==(const Graph<T>& other) const {
    if (vertexCount() != other.vertexCount() || edgeCount() != other.edgeCount()) return false;

    return checkEdgesEquality(this->edges, other.edges)
        && checkVerticesEquality(this->vertices, other.vertices);
}

template <typename T>
bool Graph<T>::operator!=(const Graph<T>& other) const {
    return !(*this == other);
}

template <typename T>
bool Graph<T>::operator<(const Graph<T>& other) const {
    if (vertexCount() != other.vertexCount()) return vertexCount() < other.vertexCount();
    return edgeCount() < other.edgeCount();
}

template <typename T>
bool Graph<T>::operator>(const Graph<T>& other) const {
    return other < *this;
}

template <typename T>
bool Graph<T>::operator<=(const Graph<T>& other) const {
    return !(*this > other);
}

template <typename T>
bool Graph<T>::operator>=(const Graph<T>& other) const {
    return !(*this < other);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Graph<T>& g) {
    os << "Vertices (" << g.vertexCount() << "):\n";

    std::for_each(g.verticesCBegin(), g.verticesCEnd(), [&](const Vertex<T>* v){
        os << "Vertex: " << v->getValue() << "\n";
    });

    os << "Edges (" << g.edgeCount() << "):\n";

    std::for_each(g.edgesCBegin(), g.edgesCEnd(), [&](const Edge<T>* e){
        os << e->getFrom()->getValue() << " -> " << e->getTo()->getValue() << "\n";
    });

    return os;
}

#endif //LAB4_GRAPHIMPLEMENTATION_H
