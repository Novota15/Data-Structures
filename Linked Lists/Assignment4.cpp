// Grant Novota
// Assignment 4
// Hoenigman

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "CommunicationNetwork.h"

using namespace std;

int printMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-To-Coast" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Quit" << endl;
    int input;
    cin >> input;
    return input;
}

int main()
{
    CommunicationNetwork Com; //initializes class
    int input = printMenu(); //prints menu and gets input
    while(input)
    {
        if(input == 1) //creates linked list and prints it
        {
            Com.buildNetwork();
            Com.printNetwork();
        }
        else if(input == 2) //prints linked list
            Com.printNetwork();
        else if(input == 3)
        {
            char message[] = "messageln.txt";
            Com.transmitMsg(message); //reads file and transmits message through cities
        }
        else if(input == 4)
        {
            string cityNew;
            string cityPrevious;
            cout << "Enter a city name: " << endl;
            cin.ignore(); //clears out the previous cin so getline will work
            getline(cin, cityNew);
            cout << "Enter a previous city name: " << endl;
            getline(cin, cityPrevious);
            Com.addCity(cityNew,cityPrevious); //adds city to linked list
        }
        else if(input == 5) //prints goodbye and breaks loop
        {
            cout << "Goodbye!" << endl;
            break;
        }
        input = printMenu();
    }
    return 0;
}
