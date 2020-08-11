#include "Queue.h"
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

Queue::Queue(int qs)
{
    queueSize = qs;
    queueHead = 0;
    queueTail = 0;
    queueCount = 0;
    arrayQueue = new string [queueSize];
}

void Queue::enqueue(string word)
{
    if(!queueIsFull()) //adds to the queue if it is not full
    {
        arrayQueue[queueTail] = word; //adding the word to the tail of the queue
        queueCount++;
        if(queueTail == queueSize-1) //moving the tail back to the front
        {
            queueTail = 0;
        }
        else
        {
            queueTail++; //moving the tail back to the next spot
        }
        cout << "E: " << word << endl;
        cout << "H: " << queueHead << endl;
        cout << "T: " << queueTail << endl;
    }
    else
    {
        cout << "Queue is full." << endl;
    }
}

string Queue::dequeue()
{
    string w = "";
    if(!queueIsEmpty()) //dequeues if the queue is not empty
    {
        w = arrayQueue[queueHead];
        queueCount--;
        if(queueHead == queueSize-1) //moves head back to the beginning
        {
            queueHead = 0;
        }
        else
        {
            queueHead++; //shifts head to the next spot
        }
        cout << "H: " << queueHead << endl;
        cout << "T: " << queueTail << endl;
        return w; //returns deleted word
    }
    else
    {
        return "Queue is empty";
    }
}

void Queue::printQueue()
{
    int y = 10;
    if(!queueIsEmpty())
    {
        if(queueTail > queueHead) //if the tail is not after the head then it must be at the front of the queue
        {
            y = queueTail;
        }
        for(int x=queueHead; x<y; x++)
        {
            cout << x << ": " << arrayQueue[x] << endl;
        }
        if(queueTail < queueHead && queueTail != 0) //if the tail is before the head it prints from begining till the tail
        {
            for(int z=0; z<queueTail; z++)
            {
                cout << z << ": " << arrayQueue[z] << endl;
            }
        }
        if(queueTail == queueHead) //if they are at the same spot then the queue prints from the beginning till that spot
            for(int i=0; i<queueTail; i++)
            {
                cout << i << ": " << arrayQueue[i] << endl;
            }
    }
    else
    {
        cout << "Empty" << endl;
    }
}

bool Queue::queueIsFull()
{
    if(queueCount == queueSize)
        return true;
    else
        return false;
}

bool Queue::queueIsEmpty()
{
    if(queueCount == 0)
        return true;
    else
        return false;
}

Queue::~Queue()
{
    //dtor
}
