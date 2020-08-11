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
    City *temp = new City(cityNew, NULL, NULL, "");
    if(cityPrevious == "First")
    {
        temp->next = current;
        current->prev = temp;
        head = temp;
    }
    else
    {
        while(current != NULL) //traversing list
        {
            if(current->cityName == cityPrevious) //looking for previous city
            {
                temp->next = current->next; //linking new city to next city
                current->next = temp; //linking previous city to new city
                temp->prev = current;
                break;
            }
            current = current->next;
        }
    }
}

void CommunicationNetwork::buildNetwork() //starting from the head, adding new nodes
{
    head = new City("Los Angeles", NULL, NULL, "");
    City *temp = new City("Phoenix", head, NULL, "");
    head->next = temp;
    temp->next = new City("Denver", temp, NULL, "");
    temp = temp->next;
    temp->next = new City("Dallas", temp, NULL, "");
    temp = temp->next;
    temp->next = new City("St. Louis", temp, NULL, "");
    temp = temp->next;
    temp->next = new City("Chicago", temp, NULL, "");
    temp = temp->next;
    temp->next = new City("Atlanta", temp, NULL, "");
    temp = temp->next;
    temp->next = new City("Washington, D.C.", temp, NULL, "");
    temp = temp->next;
    temp->next = new City("New York", temp, NULL, "");
    temp = temp->next;
    temp->next = new City("Boston", temp, NULL, "");
    tail = temp->next;
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
                cout << current->cityName << " received " << current->message << endl;
                current = current->next;
            }
            current = tail->prev;
            while(current != NULL) //traversing backward
            {
                current->message = str;
                cout << current->cityName << " received " << current->message << endl;
                current = current->prev;
            }
        }
        fs.close();
    }
}

void CommunicationNetwork::printNetwork()
{
    if(head != NULL)
    {
        cout << "===CURRENT PATH===" << endl;
        City *current = head;
        cout << "NULL <- ";
        while(current->next != NULL) //traversing through linked list
        {
            cout << current->cityName << " <-> ";
            current = current->next;
        }
        cout << current->cityName << " -> NULL" << endl;
        cout << "==================" << endl;
    }
    else //List is gone
    {
        cout << "===CURRENT PATH===" << endl;
        cout << "NULL" << endl;
        cout << "==================" << endl;
    }
}

void CommunicationNetwork::deleteCity(string cityNameDelete)
{
    City *current = head;
    while(current != NULL)//traversing through the list
    {
        if(current->cityName == cityNameDelete) //finding city to delete
        {
            if(current == head)//if city is at the head of the list
            {
                head = head->next;
                head->prev = NULL;
                delete current;
            }
            else if(current == tail)//if city is at the end of the list
            {
                tail = tail->prev;
                tail->next = NULL;
                delete current;
            }
            else//if city is in the middle of the list
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
        }
        current = current->next;
    }
}

void CommunicationNetwork::clearNetwork()
{
    if(head != NULL)
    {
        City *current = head;
        City *nextCity = current->next;
        while(current->next != NULL)//traverses until the last city
        {
            cout << "deleting " << current->cityName << endl;
            delete current;
            current = nextCity;
            nextCity = current->next;
        }
        cout << "deleting " << current->cityName << endl;
        delete current; //deletes the last city
        head = NULL;
        tail = NULL;
    }
}

CommunicationNetwork::~CommunicationNetwork()
{
    clearNetwork();
}
