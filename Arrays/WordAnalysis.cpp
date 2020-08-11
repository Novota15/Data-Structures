#include "WordAnalysis.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

WordAnalysis::WordAnalysis(int l)
{
    timesDoubled = 0;
    wordCount = 0;
    length = l;
    words = new Word[length];
    index = 0;
    x = 0;

}

void WordAnalysis::doubleArray()
{
    length = length * 2;
    Word *words2 = new Word[length];
    for(int i = 0; i < length/2; i++)
    {
        words2[i].count = words[i].count;
        words2[i].name = words[i].name;
    }
    delete []words;
    words = words2;
    timesDoubled++;
}

bool WordAnalysis::checkIfCommonWord(string w)
{
    bool uniqueWord = true;
    string commonWords[] = {"the", "you", "one", "be", "do", "all", "to", "at", "would", "of", "this", "there", "and", "but", "their", "a", "his", "what", "in", "by", "so", "that", "from", "up", "have", "they", "out", "i", "we", "if", "it", "say", "about", "for", "her", "who", "not", "she", "get", "on", "or", "which", "with", "an", "go", "he", "will", "me", "as", "my"};
    for(int i = 0; i < 50; i++)
    {
        if(w == commonWords[i]) //if the word is found in the array of common words, the word is not unique
        {
            uniqueWord = false;
            break;
        }
    }
    return uniqueWord;
}

void WordAnalysis::sortData()
{
    for(int z=0; z < length-1; z++)
    {
        for(int y=0; y < length-z-1; y++)
        {
            //sorted into descending order
            if(words[y].count < words[y+1].count)
            {
                Word swap = words[y];
                words[y] = words[y+1];
                words[y+1] = swap;
            }
        }
    }
}

bool WordAnalysis::readDataFile(string filename)
{
    ifstream fs;
    string str;
    fs.open(filename);

    while(!fs.eof())
    {
        bool match = false;
        fs >> str;

        if(x == length)
        {
            WordAnalysis::doubleArray();
        }
        for(int i=0; i<length; i++)
        {
            if(words[i].name == str)
            {
                words[i].count = words[i].count+1;
                match = true;
                wordCount++;
                break;
            }
        }
        if(match == false && WordAnalysis::checkIfCommonWord(str) == true)
        {
            words[x].name = str;
            words[x].count = 1;
            wordCount++;
            index++;
            x++;
        }
    }
    WordAnalysis::sortData();
    return true;
}

int WordAnalysis::getWordCount()
{
    return wordCount;
}

int WordAnalysis::getUniqueWordCount()
{
    return index;
}

int WordAnalysis::getArrayDoubling()
{
    return timesDoubled;
}

void WordAnalysis::printCommonWords(int n)
{
    for(int i=0; i < n; i++)
    {
        cout << words[i].count << " - " << words[i].name << endl;
    }
}

WordAnalysis::~WordAnalysis()
{
    //dtor
}
