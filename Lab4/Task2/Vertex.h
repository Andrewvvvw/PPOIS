#ifndef LAB4_VERTEX_H
#define LAB4_VERTEX_H

template <typename T>
class Edge;

template <typename T>
class Vertex {
public:
    explicit Vertex(const T& val) : value(val) {}
    const T& getValue() const {
        return value;
    }
    T& getValue() {
        return value;
    }

    Edge<T>* getFirstOut() const {
        return firstOut;
    }
    void setFirstOut(Edge<T>* e) {
        firstOut = e;
    }

    Edge<T>* getFirstIn() const {
        return firstIn;
    }
    void setFirstIn(Edge<T>* e) {
        firstIn = e;
    }

private:
    T value;
    Edge<T>* firstOut = nullptr;
    Edge<T>* firstIn = nullptr;
};

#endif //LAB4_VERTEX_H
