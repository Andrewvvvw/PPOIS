#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <memory>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include "VertexIterator.h"
#include "Vertex.h"
#include "Edge.h"
#include "EdgeIterator.h"
#include "IncidentEdgeIterator.h"
#include "AdjacentVertexIterator.h"

template <typename T>
class Graph {
public:
    using value_type = Vertex<T>*;
    using reference = Vertex<T>*&;
    using const_reference = const Vertex<T>*&;
    using pointer = Vertex<T>*;
    using const_pointer = const Vertex<T>*;
    using size_type = std::size_t;

    using vertex_iterator = VertexIterator<T>;
    using const_vertex_iterator = ConstVertexIterator<T>;
    using reverse_vertex_iterator = ReverseVertexIterator<T>;
    using const_reverse_vertex_iterator = ConstReverseVertexIterator<T>;

    using edge_iterator = EdgeIterator<T>;
    using const_edge_iterator = ConstEdgeIterator<T>;
    using reverse_edge_iterator = ReverseEdgeIterator<T>;
    using const_reverse_edge_iterator = ConstReverseEdgeIterator<T>;

    using incident_edge_iterator = IncidentEdgeIterator<T>;
    using const_incident_edge_iterator = ConstIncidentEdgeIterator<T>;
    using reverse_incident_edge_iterator = ReverseIncidentEdgeIterator<T>;
    using const_reverse_incident_edge_iterator = ConstReverseIncidentEdgeIterator<T>;

    using adjacent_vertex_iterator = AdjacentVertexIterator<T>;
    using const_adjacent_vertex_iterator = ConstAdjacentVertexIterator<T>;
    using reverse_adjacent_vertex_iterator = ReverseAdjacentVertexIterator<T>;
    using const_reverse_adjacent_vertex_iterator = ConstReverseAdjacentVertexIterator<T>;

private:
    std::vector<Vertex<T>*> vertices;
    std::vector<Edge<T>*> edges;

    bool checkVerticesEquality(std::vector<Vertex<T>*> verticesFirstGraph, std::vector<Vertex<T>*> verticesSecondGraph);
    bool checkEdgesEquality(std::vector<Edge<T>*> edgesFirstGraph, std::vector<Edge<T>*> edgesSecondGraph);
public:
    Graph();
    ~Graph();
    Graph(const Graph& other);

    bool empty() const;
    void clear();

    Vertex<T>* addVertex(const T& value);
    Vertex<T>* getVertex(size_type index) const;
    std::size_t vertexCount() const;

    Edge<T>* addEdge(Vertex<T>* from, Vertex<T>* to);
    Edge<T>* addEdge(size_type fromIndex, size_type toIndex);
    std::size_t edgeCount() const;

    bool containsVertex(const Vertex<T>* v) const;
    bool containsEdge(const Vertex<T>* from, const Vertex<T>* to) const;

    std::size_t outDegree(const Vertex<T>* v) const;
    std::size_t inDegree(const Vertex<T>* v) const;
    std::size_t vertexDegree(const Vertex<T>* v) const;
    std::size_t edgeDegree(const Edge<T>* e) const;

    bool removeVertex(Vertex<T>* v);
    bool removeEdge(Edge<T>* e);

    bool removeVertex(vertex_iterator it);
    bool removeVertex(const_vertex_iterator it);

    bool removeEdge(edge_iterator it);
    bool removeEdge(const_edge_iterator it);

    vertex_iterator verticesBegin();
    vertex_iterator verticesEnd();
    const_vertex_iterator verticesCBegin() const;
    const_vertex_iterator verticesCEnd() const;
    reverse_vertex_iterator verticesRBegin();
    reverse_vertex_iterator verticesREnd();
    const_reverse_vertex_iterator verticesCRBegin() const;
    const_reverse_vertex_iterator verticesCREnd() const;

    edge_iterator edgesBegin();
    edge_iterator edgesEnd();
    const_edge_iterator edgesCBegin() const;
    const_edge_iterator edgesCEnd() const;
    reverse_edge_iterator edgesRBegin();
    reverse_edge_iterator edgesREnd();
    const_reverse_edge_iterator edgesCRBegin() const;
    const_reverse_edge_iterator edgesCREnd() const;

    incident_edge_iterator incidentEdgesBegin(Vertex<T>* v, bool outgoing = true);
    incident_edge_iterator incidentEdgesEnd(Vertex<T>* v, bool outgoing = true);
    const_incident_edge_iterator incidentEdgesCBegin(const Vertex<T>* v, bool outgoing = true) const;
    const_incident_edge_iterator incidentEdgesCEnd(const Vertex<T>* v, bool outgoing = true) const;
    reverse_incident_edge_iterator incidentEdgesRBegin(Vertex<T>* v, bool outgoing = true);
    reverse_incident_edge_iterator incidentEdgesREnd(Vertex<T>* v, bool outgoing = true);
    const_reverse_incident_edge_iterator incidentEdgesCRBegin(const Vertex<T>* v, bool outgoing = true) const;
    const_reverse_incident_edge_iterator incidentEdgesCREnd(const Vertex<T>* v, bool outgoing = true) const;

    adjacent_vertex_iterator adjacentBegin(Vertex<T>* v);
    adjacent_vertex_iterator adjacentEnd(Vertex<T>* v);
    const_adjacent_vertex_iterator adjacentCBegin(const Vertex<T>* v) const;
    const_adjacent_vertex_iterator adjacentCEnd(const Vertex<T>* v) const;
    reverse_adjacent_vertex_iterator adjacentRBegin(Vertex<T>* v);
    reverse_adjacent_vertex_iterator adjacentREnd(Vertex<T>* v);
    const_reverse_adjacent_vertex_iterator adjacentCRBegin(const Vertex<T>* v) const;
    const_reverse_adjacent_vertex_iterator adjacentCREnd(const Vertex<T>* v) const;

    Graph<T>& operator=(const Graph<T>& other);
    bool operator>(const Graph& other) const;
    bool operator<(const Graph& other) const;
    bool operator>=(const Graph& other) const;
    bool operator<=(const Graph& other) const;
    bool operator==(const Graph& other) const;
    bool operator!=(const Graph& other) const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Graph<U>& graph);
};

#include "GraphImplementation.h"

#endif // GRAPH_H
