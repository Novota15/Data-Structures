// Grant Novota
// Assignment 12
// Hoenigman

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "Graph.h"

using namespace std;

Graph<string> g;

int printMenu()
{
    int input;
    cout << "======Main Menu======" << endl;
    cout << "1. Print vertices" << endl;
    cout << "2. Find districts" << endl;
    cout << "3. Find shortest path" << endl;
    cout << "4. Quit" << endl;
    cin >> input;
    return input;
}

void readFile(string filename)
{
    ifstream fs;
    string line;
    vector<string> cities;
    string fromCity;
    string toCity;
    int index = 0;
    int weight;

    fs.open(filename);
    if(!fs)
    {
        cout << "Could not open file" << endl;
    }
    else
    {
        while(getline(fs, line))
        {
            istringstream ss(line);
            string token;
            getline(ss, token, ',');
            //cout << token << endl;
            if(token == "cities")
            {
                while(getline(ss, token, ','))
                {
                    //collect all cities so that it can be used later while adding an edge
                    cities.push_back(token);
                    //add it as a vertex in graph g as well
                    g.addVertex(token);
                    if(token == "Seattle")
                        break;
                }
                //continue reading next line
                g.addVertex("Yakima");
                continue;
            }
            fromCity = token;
            index = 0;
            while(getline(ss, token, ','))
            {
                //add the edges
                toCity = cities[index];
                //add edge fromCity, toCity with weight to the graph
                istringstream buffer(token);
                buffer >> weight;
                g.addEdge(fromCity, toCity, weight);
                //cout << weight;
                index++;
            }
            //cout << "" << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    string filename = argv[1];
    //string filename = "zombieCities.txt";
    readFile(filename);

    int input = printMenu();
    while(input)
    {
        if(input == 1) //print vertices
        {
            g.displayEdges();
        }
        else if(input == 2) //find districts
        {

        }
        else if(input == 3) //find shortest path
        {
            cout << "Enter a starting city:" << endl;
            string startCity;
            cin.ignore();
            getline(cin, startCity);
            cout << "Enter an ending city:" << endl;
            string endCity;
            cin.ignore();
            getline(cin, endCity);
            //g.findShortestPath(startCity, endCity);
        }
        else if(input == 4) //quit
        {
            cout << "Goodbye!" << endl;
            break;
        }
        input = printMenu();
    }
    return 0;
}
