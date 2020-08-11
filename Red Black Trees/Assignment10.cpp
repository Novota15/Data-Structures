// Grant Novota
// Assignment 10
// Hoenigman

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "MovieTree.h"

using namespace std;

MovieTree mt;

int printMenu()
{
    int input;
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Count the longest path" << endl;
    cout << "7. Quit" << endl;
    cin >> input;
    return input;
}

void readFile(string filename)
{
    ifstream fs;
    string line;
    fs.open(filename);
    if(!fs)
    {
        cout << "Could not open file" << endl;
    }
    else
    {
        string data[4];
        int index = 0;
        while(getline(fs, line))
        {
            istringstream ss(line);
            string token;
            while(getline(ss, token, ',')) //adds each movie's data to the tree
            {
                if(index == 4)
                {
                    istringstream buffer(data[0]);
                    int ranking;
                    buffer >> ranking;
                    string title = data[1];
                    istringstream buffer2(data[2]);
                    int year;
                    buffer2 >> year;
                    istringstream buffer3(data[3]);
                    int quantity;
                    buffer3 >> quantity;
                    mt.addMovieNode(ranking, title, year, quantity);
                    index = 0;
                }
                data[index] = token;
                index++;
            }
        } //now to add the final movie
        istringstream buffer4(data[0]);
        int ranking;
        buffer4 >> ranking;
        string title = data[1];
        istringstream buffer5(data[2]);
        int year;
        buffer5 >> year;
        istringstream buffer6(data[3]);
        int quantity;
        buffer6 >> quantity;
        mt.addMovieNode(ranking, title, year, quantity);
    }
}

int main(int argc, char *argv[])
{
    string filename = argv[1];

    readFile(filename);

    int input = printMenu();
    while(input)
    {
        if(input == 1)
        {
            cout << "Enter title:";
            string movie;
            cin.ignore();
            getline(cin, movie);
            mt.findMovie(movie);
        }
        else if(input == 2)
        {
            cout << "Enter title:";
            string rental;
            cin.ignore();
            getline(cin, rental);
            mt.rentMovie(rental);
        }
        else if(input == 3)
        {
            mt.printMovieInventory();
        }
        else if(input == 4)
        {
            cout << "Enter title:";
            string del;
            cin.ignore();
            getline(cin, del);
            mt.deleteMovieNode(del);
            cout << endl;
        }
        else if(input == 5)
        {
            cout << "Tree contains: " << mt.countMovieNodes() << " movies." << endl;
        }
        else if(input == 6)
        {
            cout << "Longest Path: " << mt.countLongestPath() << endl;
        }
        else if(input == 7)
        {
            cout << "Goodbye!" << endl;
            break;
        }
        input = printMenu();
    }
    return 0;
}
