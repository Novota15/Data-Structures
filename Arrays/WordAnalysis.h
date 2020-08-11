#ifndef WORDANALYSIS_H
#define WORDANALYSIS_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct Word //contains the word and how many times that word appears in the text
{
    string name = "";
    int count = 0;
};

class WordAnalysis
{
    private:
        int timesDoubled; //number of times the array has been doubled
        Word *words; //array of words
        int wordCount; //current size of the array
        int index; //how many unique words found
        int length;
        int x;

        void doubleArray();
        bool checkIfCommonWord(string);
        void sortData();

    public:
        bool readDataFile(string); //returns an error if file not opened
        int getWordCount(); //returns index *count for each word
        int getUniqueWordCount(); //returns index variable
        int getArrayDoubling(); //returns timesDoubled variable
        void printCommonWords(int);
        WordAnalysis(int); //constructor. Argument is the initial size of the array
        virtual ~WordAnalysis();
};

#endif // WORDANALYSIS_H
