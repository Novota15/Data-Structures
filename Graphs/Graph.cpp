#include <queue>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

template<class T>
Graph<T>::Graph()
{

}

template<class T>
Graph<T>::~Graph()
{
    //dtor

}

template<class T>
void Graph<T>::addEdge(T v1, T v2, int weight){ //key values for starting and ending vertices and the edge weight
    //loop through vertices and find v1
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            //find the second one
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    //add to adjacent vector for v1
                    adjVertex<T> av; //instance
                    av.v = &vertices[j]; //pointer
                    av.weight = weight;
                    vertices[i].adj.push_back(av);

                    //add edge in the other direction
                    //vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    //adjVertex<T> av2;
                    //av2.v = &vertices[i];
                    //av2.weight = weight;
                    //vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}

template<class T>
void Graph<T>::addVertex(T n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex<T> v;
        v.name = n;
        v.district = -1;
        vertices.push_back(v);
        //cout << v.name << " was added." << endl;
    }
}

template<class T>
void Graph<T>::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<< vertices[i].district << ":" << vertices[i].name << "-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            if(vertices[i].adj[j].weight != -1)
                cout<<vertices[i].adj[j].v->name<<"***";
        }
        cout<<endl;
    }
}

/*template<class T>
void Graph<T>::findShortestPath(string startValue, string endValue)
{
    string city = breadthFirstSearch(startValue, endValue);
}
*/
/*template<class T>
string Graph<T>::breadthFirstSearch(string startValue, string endValue)
{
    vertex<T> *v;
    for(int i=0; i < vertices.size(); i++)
    {
        if(vertices[i].name == startValue)
        {
            *v = vertices[i];
            break;
        }
    }
    v->visited = true;
    v->distance = 0;
    v->parent = NULL;
    queue<vertex<T>> q;
    q.push_back(v);
    while(!q.isEmpty())
    {
        vertex<T> *n = q.pop();
        for(int x=0; x < n->adj[x].size(); x++)
        {
            if(!n->adj[x].v->visited)
            {
                n->adj[x].v->distance = n->distance + 1;
                n->adj[x].v->parent = n;
                if(n->adj[x].v->name == endValue)
                    return n->adj[x].v;
                else
                {
                    n->adj[x].v->visited = true;
                    q.pop(n->adj[x].v);
                }
            }
        }
    }
    return NULL;
}
*/


