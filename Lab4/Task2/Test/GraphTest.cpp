#include "UnitTest++.h"
#include "../Graph.h"
#include <sstream>
#include <vector>
#include <algorithm>

TEST(GraphConstruction) {
    Graph<int> g;
            CHECK(g.empty());
            CHECK_EQUAL(0, g.vertexCount());
            CHECK_EQUAL(0, g.edgeCount());
}

TEST(VertexOperations) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
            CHECK(!g.empty());
            CHECK_EQUAL(2, g.vertexCount());
            CHECK(g.containsVertex(v1));
            CHECK(g.containsVertex(v2));
            CHECK(!g.containsVertex(nullptr));
}

TEST(EdgeOperations) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    auto e1 = g.addEdge(v1, v2);
            CHECK_EQUAL(1, g.edgeCount());
            CHECK(g.containsEdge(v1, v2));
            CHECK(!g.containsEdge(v2, v1));
}

TEST(DegreeFunctions) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    auto v3 = g.addVertex(3);
    g.addEdge(v1, v2);
    g.addEdge(v3, v1);
            CHECK_EQUAL(1, g.outDegree(v1));
            CHECK_EQUAL(1, g.inDegree(v1));
            CHECK_EQUAL(0, g.outDegree(v2));
            CHECK_EQUAL(1, g.inDegree(v2));
            CHECK_EQUAL(2, g.vertexDegree(v1));
            CHECK_EQUAL(2, g.edgeDegree(v1->getFirstOut()));
}

TEST(RemoveVertexEdge) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    auto v3 = g.addVertex(3);
    auto e1 = g.addEdge(v1, v2);
    auto e2 = g.addEdge(v2, v3);
            CHECK(g.removeEdge(e1));
            CHECK_EQUAL(1, g.edgeCount());
            CHECK(!g.containsEdge(v1, v2));
            CHECK(g.removeVertex(v2));
            CHECK_EQUAL(2, g.vertexCount());
            CHECK(!g.containsVertex(v2));
}

TEST(VertexIterator) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    int sum = 0;
    for (auto it = g.verticesBegin(); it != g.verticesEnd(); ++it) sum += (*it)->getValue();
            CHECK_EQUAL(3, sum);
    sum = 0;
    for (auto it = g.verticesRBegin(); it != g.verticesREnd(); ++it) sum += (*it)->getValue();
            CHECK_EQUAL(3, sum);
    sum = 0;
    for (auto it = g.verticesCBegin(); it != g.verticesCEnd(); ++it) sum += (*it)->getValue();
            CHECK_EQUAL(3, sum);
    sum = 0;
    for (auto it = g.verticesCRBegin(); it != g.verticesCREnd(); ++it) sum += (*it)->getValue();
            CHECK_EQUAL(3, sum);
}

TEST(EdgeIterator) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    auto e = g.addEdge(v1, v2);
    int sum = 0;
    for (auto it = g.edgesBegin(); it != g.edgesEnd(); ++it) sum += (*it)->getFrom()->getValue();
            CHECK_EQUAL(1, sum);
    sum = 0;
    for (auto it = g.edgesRBegin(); it != g.edgesREnd(); ++it) sum += (*it)->getFrom()->getValue();
            CHECK_EQUAL(1, sum);
}

TEST(IncidentEdgeIterator) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    auto e = g.addEdge(v1, v2);
    int sum = 0;
    for (auto it = g.incidentEdgesBegin(v1); it != g.incidentEdgesEnd(v1); ++it) sum += (*it)->getTo()->getValue();
            CHECK_EQUAL(2, sum);
    sum = 0;
    for (auto it = g.incidentEdgesRBegin(v1); it != g.incidentEdgesREnd(v1); ++it) sum += (*it)->getTo()->getValue();
            CHECK_EQUAL(2, sum);
    sum = 0;
    for (auto it = g.incidentEdgesCBegin(v1); it != g.incidentEdgesCEnd(v1); ++it) sum += (*it)->getTo()->getValue();
            CHECK_EQUAL(2, sum);
    sum = 0;
    for (auto it = g.incidentEdgesCRBegin(v1); it != g.incidentEdgesCREnd(v1); ++it) sum += (*it)->getTo()->getValue();
            CHECK_EQUAL(2, sum);
}

TEST(AdjacentVertexIterator) {
    Graph<int> g;
    auto v1 = g.addVertex(1);
    auto v2 = g.addVertex(2);
    auto v3 = g.addVertex(3);
    g.addEdge(v1, v2);
    g.addEdge(v1, v3);
    int sum = 0;
    for (auto it = g.adjacentBegin(v1); it != g.adjacentEnd(v1); ++it) sum += (*it)->getValue();
            CHECK_EQUAL(5, sum);
    sum = 0;
    for (auto it = g.adjacentRBegin(v1); it != g.adjacentREnd(v1); ++it) sum += (*it)->getValue();
            CHECK_EQUAL(5, sum);
    sum = 0;
    for (auto it = g.adjacentCBegin(v1); it != g.adjacentCEnd(v1); ++it) sum += (*it)->getValue();
            CHECK_EQUAL(5, sum);
    sum = 0;
    for (auto it = g.adjacentCRBegin(v1); it != g.adjacentCREnd(v1); ++it) sum += (*it)->getValue();
            CHECK_EQUAL(5, sum);
}

TEST(CopyAndAssignment) {
    Graph<int> g1;
    auto v1 = g1.addVertex(1);
    auto v2 = g1.addVertex(2);
    g1.addEdge(v1, v2);
    Graph<int> g2(g1);
            CHECK_EQUAL(g1.vertexCount(), g2.vertexCount());
            CHECK_EQUAL(g1.edgeCount(), g2.edgeCount());
    Graph<int> g3;
    g3 = g1;
            CHECK_EQUAL(g1.vertexCount(), g3.vertexCount());
            CHECK_EQUAL(g1.edgeCount(), g3.edgeCount());
}

TEST(ComparisonOperators) {
    Graph<int> g1;
    Graph<int> g2;
    auto v1 = g1.addVertex(1);
    auto v2 = g1.addVertex(2);
    g1.addEdge(v1, v2);
    auto u1 = g2.addVertex(1);
    auto u2 = g2.addVertex(2);
    g2.addEdge(u1, u2);
            CHECK(g1 == g2);
            CHECK(!(g1 != g2));
    g2.addVertex(3);
            CHECK(g1 < g2);
            CHECK(g2 > g1);
            CHECK(g1 <= g2);
            CHECK(g2 >= g1);
}
