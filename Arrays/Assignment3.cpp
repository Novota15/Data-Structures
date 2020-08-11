// Grant Novota
// Assignment 3
// Hoenigman

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "WordAnalysis.h"

using namespace std;

int main(int argc, char *argv[])
{
    string filename = argv[1];
    string n = argv[2];

    int numWords = 0;
    istringstream convert(n);
    convert >> numWords;

    WordAnalysis wa(100);

    bool dataRead = false;

    dataRead = wa.readDataFile(filename);

    wa.printCommonWords(numWords);
    cout << "#" << endl;
    cout << "Array doubled: " << wa.getArrayDoubling() << endl;
	cout << "#" << endl;
	cout << "Unique non-common words: " << wa.getUniqueWordCount() << endl;
	cout << "#" << endl;
	cout << "Total non-common words: " << wa.getWordCount() << endl;




    return 0;
}
