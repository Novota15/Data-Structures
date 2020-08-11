// Grant Novota
// Assignment 6
// Hoenigman

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "Queue.h"

using namespace std;

int printMenu()
{
    int input;
    cout << "======Main Menu=====" << endl;
    cout << "1. Enqueue word" << endl;
    cout << "2. Dequeue word" << endl;
    cout << "3. Print queue" << endl;
    cout << "4. Enqueue sentence" << endl;
    cout << "5. Quit" << endl;
    cin >> input;
    return input;
}

int main()
{
    Queue Q(10);
    string word = "";
    string sequence = "";
    int input = printMenu();
    while(input)
    {
        if(input == 1)
        {
            cout << "word: "; //<< endl;
            cin >> word;
            Q.enqueue(word);
        }
        else if(input == 2)
        {
            string x = Q.dequeue();
            if(x == "Queue is empty")
                cout << "Queue is empty." << endl;
            else
                cout << "word: " << x << endl;
        }
        else if(input == 3)
        {
            Q.printQueue();
        }
        else if(input == 4)
        {
            cout << "sentence: ";
            cin.ignore();
            getline(cin, sequence);
            istringstream iss(sequence);
            string w;
            while(iss >> w)
            {
                Q.enqueue(w);
            }
        }
        else if(input == 5)
        {
            cout << "Goodbye!" << endl;
            break;
        }
        input = printMenu();
    }
}
