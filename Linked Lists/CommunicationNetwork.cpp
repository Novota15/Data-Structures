#include "CommunicationNetwork.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
using namespace std;

CommunicationNetwork::CommunicationNetwork()
{
    //ctor
}

void CommunicationNetwork::addCity(string cityNew, string cityPrevious)
{
    City *current = head;
    City *temp = new City(cityNew, NULL, "");
    while(current != NULL) //traversing list
    {
        if(current->cityName == cityPrevious) //loosing for previous city
        {
            temp->next = current->next; //linking new city to next city
            current->next = temp; //linking previous city to new city
            break;
        }
        current = current->next;
    }
}

void CommunicationNetwork::buildNetwork() //starting from the head, adding new nodes
{
    head = new City("Los Angeles", NULL, "");
    City *temp = new City("Phoenix", NULL, "");
    head->next = temp;
    temp->next = new City("Denver", NULL, "");
    temp = temp->next;
    temp->next = new City("Dallas", NULL, "");
    temp = temp->next;
    temp->next = new City("St. Louis", NULL, "");
    temp = temp->next;
    temp->next = new City("Chicago", NULL, "");
    temp = temp->next;
    temp->next = new City("Atlanta", NULL, "");
    temp = temp->next;
    temp->next = new City("Washington, D.C.", NULL, "");
    temp = temp->next;
    temp->next = new City("New York", NULL, "");
    temp = temp->next;
    temp->next = new City("Boston", NULL, "");
    tail = temp;
}

void CommunicationNetwork::transmitMsg(char *filename)
{
    if(head == NULL)
    {
        cout << "Empty list" << endl;
    }
    else
    {
        ifstream fs;
        string str;
        fs.open(filename);
        while(!fs.eof())
        {
            fs >> str;
            City *current = head;
            while(current != NULL) //traversing through list
            {
                current->message = str; //setting the message equal to the word in the file
                cout << current->cityName << " received " << str << endl;
                current = current->next;
            }
        }
        fs.close();
    }
}

void CommunicationNetwork::printNetwork()
{
    cout << "===CURRENT PATH===" << endl;
    City *current = head;
    while(current != NULL) //traversing through linked list
    {
        cout << current->cityName << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
    cout << "==================" << endl;
}

CommunicationNetwork::~CommunicationNetwork()
{
    //dtor
}
