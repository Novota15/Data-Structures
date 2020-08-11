#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>
using namespace std;

template<class T>
struct vertex;

template<class T>
struct adjVertex{
    vertex<T> *v;
    int weight;
};

template<class T>
struct vertex{
    T name;
    int district;
    bool visited;
    int distance;
    vertex<T> *parent;
    std::vector<adjVertex<T> > adj;
};

template<class T>
class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(T v1, T v2, int weight);
        void addVertex(T name);
        void displayEdges();
        //void findShortestPath(string startValue, string endValue);
        //string breadthFirstSearch(string startValue, string endValue);
    protected:
    private:
        std::vector<vertex<T> > vertices;

};
#include "Graph.cpp"
#endif // GRAPH_H
