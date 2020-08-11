//Grant Novota
//Assignment 10
#include "MovieTree.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
using namespace std;

MovieTree::MovieTree()
{
    nil = new MovieNode(0, "", 0, 0);
    nil->isRed = false;
    nil->leftChild = nil->rightChild = nil;
    root = nil;
}

void MovieTree::printMovieInventory()
{
    printMovieInventory(root);
}

int MovieTree::countMovieNodes()
{
    int count = countMovieNodes(root);
    return count;
}

void MovieTree::deleteMovieNode(string title)
{
    MovieNode *n = root;
    while(n != nil) //finds node to delete
    {
        if(title < n->title)
            n = n->leftChild;
        else if(title > n->title)
            n = n->rightChild;
        else
            break;
    }
    if(n == nil)
    {
        cout << "Movie not found." << endl;
    }
    else
    {
        rbDelete(n); //sends node to delete function
    }
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity)
{
   //adds to the bst like normal
    MovieNode *newNode = new MovieNode(ranking, title, releaseYear, quantity);
    MovieNode *tmp = root;
    MovieNode *parent = nil;
    while(tmp != nil)
    {
        parent = tmp;
        if(newNode->title < tmp->title)
            tmp = tmp->leftChild;
        else
            tmp = tmp->rightChild;
    }
    if(parent == nil)
    {
        root = newNode;
        root->parent = nil;
    }
    else if(newNode->title < parent->title)
    {
        parent->leftChild = newNode;
        newNode->parent = parent;
    }
    else
    {
        parent->rightChild = newNode;
        newNode->parent = parent;
    }
    newNode->leftChild = nil;
    newNode->rightChild = nil;
    newNode->isRed = true;
    rbAddFixup(newNode); //makes the tree a valid rb tree
}

void MovieTree::findMovie(string title)
{
    MovieNode *movie = searchMovieTree(root, title);
    if(movie != nil)
    {
        cout << endl << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << movie->ranking << endl;
        cout << "Title:" << movie->title << endl;
        cout << "Year:" << movie->year << endl;
        cout << "Quantity:" << movie->quantity << endl;
    }
    else
        cout << endl << "Movie not found." << endl;
}

void MovieTree::rentMovie(string title)
{
    MovieNode *movie = searchMovieTree(root, title);
    if(movie != nil)
    {
        movie->quantity = movie->quantity - 1;
        cout << endl << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << movie->ranking << endl;
        cout << "Title:" << movie->title << endl;
        cout << "Year:" << movie->year << endl;
        cout << "Quantity:" << movie->quantity << endl;
        if(movie->quantity == 0)
        {
            deleteMovieNode(title);
        }
    }
    else
        cout << endl << "Movie not found." << endl;
}

bool MovieTree::isValid()
{

}

int MovieTree::countLongestPath()
{
    return countLongestPath(root);
}

//private functions:

void MovieTree::DeleteAll(MovieNode *node) //post order traversal
{
    if(node != nil)
    {
        if(node->leftChild != nil)
            DeleteAll(node->leftChild);
        if(node->rightChild != nil)
            DeleteAll(node->rightChild);
        cout << "Deleting: " << node->title << endl;
        delete node;
    }
}

void MovieTree::printMovieInventory(MovieNode *node)
{
    MovieNode *current = new MovieNode;
    MovieNode *pre = new MovieNode;
    if(root == nil)
        cout << "Empty" << endl;
    current = node;
    while (current != nil)
    {
        if(current->leftChild == nil)
        {
            cout << "Movie: " << current->title << " " << current->quantity << endl;
            current = current->rightChild;
        }
        else
        {
            pre = current->leftChild;
            while(pre->rightChild != nil && pre->rightChild != current)
            {
                pre = pre->rightChild;
            }
            if(pre->rightChild == nil)
            {
                pre->rightChild = current;
                current = current->leftChild;
            }
            else
            {
                pre->rightChild = nil;
                cout << "Movie: " << current->title << " " << current->quantity << endl;
                current = current->rightChild;
            }
        }
    }
}

void MovieTree::rbAddFixup(MovieNode *node)
{
    MovieNode *x = node;
    while((x != root) && (x->parent->isRed == true))
    {
        if(x->parent == x->parent->parent->leftChild)
        {
            MovieNode *uncle = x->parent->parent->rightChild;
            if(uncle->isRed == true)
            {
                x->parent->isRed = false;
                uncle->isRed = false;
                x->parent->parent->isRed = true;
                x = x->parent->parent;
            }
            else
            {
                if(x == x->parent->rightChild)
                {
                    x = x->parent;
                    leftRotate(x); //x is now a left child
                }
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                rightRotate(x->parent->parent);
            }
        }
        else
        {
            MovieNode *uncle = x->parent->parent->leftChild;
            if(uncle->isRed == true)
            {
                x->parent->isRed = false;
                uncle->isRed = false;
                x->parent->parent->isRed = true;
                x = x->parent->parent;
            }
            else
            {
                if(x == x->parent->leftChild)
                {
                    x = x->parent;
                    rightRotate(x); //x is now a left child
                }
                x->parent->isRed = false;
                x->parent->parent->isRed = true;
                leftRotate(x->parent->parent);
            }
        }
    }
    root->isRed = false;
}

void MovieTree::leftRotate(MovieNode *x)
{
    MovieNode *y = x->rightChild;
    x->rightChild = y->leftChild;
    if(y->leftChild != nil)
        y->leftChild->parent = x;
    y->parent = x->parent;
    if(x->parent == nil)
        root = y;
    else
    {
        if(x == x->parent->leftChild)
            x->parent->leftChild = y;
        else
            x->parent->rightChild = y;
    }
    y->leftChild = x;
    x->parent = y;
}

void MovieTree::rbDelete(MovieNode *n)
{
    bool nodeRed = n->isRed;
    MovieNode *x = new MovieNode;
    if(n->rightChild != nil) //two children
    {
        MovieNode *right = n->rightChild;
        nodeRed = right->isRed; //color of replacement
        x = right->rightChild;
        if(n->leftChild != nil)
            right->leftChild = n->leftChild;
        if(n->parent->rightChild == n)
            n->parent->rightChild = right;
        else
            n->parent->leftChild = right;
        right->parent = n->parent;
        right->isRed = n->isRed;
    }
    else if(n->leftChild != nil) //one child
    {
        MovieNode *left = n->leftChild;
        x = left;
        if(n->parent->rightChild == n)
            n->parent->rightChild = left;
        else
            n->parent->leftChild = left;
        left->parent = n->parent;
    }
    else //no children
    {
        if(n->parent->rightChild == n)
            n->parent->rightChild = nil;
        else
            n->parent->leftChild = nil;
    }
    //if(nodeRed == false)
     //   rbDeleteFixup(x);
    delete n;
}

void MovieTree::rightRotate(MovieNode *y)
{
    MovieNode *x = y->leftChild;
    y->leftChild = x->rightChild;
    if(x->rightChild != nil)
        x->rightChild->parent = y;
    x->parent = y->parent;
    if(y->parent == nil)
        root = x;
    else if(y == y->parent->leftChild)
        y->parent->leftChild = x;
    else
        y->parent->rightChild = x;
    x->rightChild = y;
    y->parent = x;
}

void MovieTree::rbDeleteFixup(MovieNode *x)
{
    MovieNode *s = new MovieNode;
    while ((x != root) && (x->isRed == false))
    {
        if(x == x->parent->leftChild)
        {
            s = x->parent->rightChild;
            if(s->isRed == true) //case 1
            {
                s->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                s = x->parent->rightChild;
            }
            if((s->leftChild->isRed == false) && (s->rightChild->isRed == false)) //case 2
            {
                s->isRed = true;
                x = x->parent;
            }
            else if((s->leftChild->isRed == true) && (s->rightChild->isRed == false)) //case 3
            {
                s->leftChild->isRed = false;
                s->isRed = true;
                rightRotate(s);
                s = x->parent->rightChild;
            }
            else
            {
                s->isRed = x->parent->isRed; //case 4
                x->parent->isRed == false;
                s->rightChild->isRed = false;
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            //left and right exchanged?
        }
    }
    x->isRed = false;
}

void MovieTree::rbTransplant(MovieNode *u, MovieNode *v)
{

}
//Returns 0 if the tree is invalid, otherwise returns the black node height
int MovieTree::rbValid(MovieNode *node)
{
    int lh = 0;
    int rh = 0;

    //If we are at a nil node just return 1
    if(node == nil)
        return 1;
    else
    {
        //First check for consecutive red links.
        if(node->isRed)
        {
            if(node->leftChild->isRed || node->rightChild->isRed)
            {
                cout << "This tree contains a red violation" << endl;
                return 0;
            }
        }
        //Check for valid binary search tree.
        if((node->leftChild != nil && node->leftChild->title.compare(node->title) > 0) || (node->rightChild != nil && node->rightChild->title.compare(node->title) < 0))
        {
            cout << "This tree contains a binary tree violation" << endl;
            return 0;
        }
        //Determine the height of left and right children.
        lh = rbValid(node->leftChild);
        rh = rbValid(node->rightChild);
        //Black height mismatch.
        if(lh != 0 && rh != 0 && lh != rh)
        {
            cout << "This tree contains a black height violation" << endl;
            return 0;
        }
        //If neither height is zero, increment it if black.
        if(lh != 0 && rh != 0)
        {
            if(node->isRed)
                return lh;
            else
                return lh+1;
        }
        else
            return 0;
    }
}

int MovieTree::countMovieNodes(MovieNode *node) //traverses through entire tree
{
    MovieNode *current = new MovieNode;
    MovieNode *pre = new MovieNode;
    int count = 0; //count is incremented for every movie node in the tree
    if(root == nil)
        cout << "Empty" << endl;
    current = node;
    while (current != nil)
    {
        if(current->leftChild == nil)
        {
            count++;
            current = current->rightChild;
        }
        else
        {
            pre = current->leftChild;
            while(pre->rightChild != nil && pre->rightChild != current)
            {
                pre = pre->rightChild;
            }
            if(pre->rightChild == nil)
            {
                pre->rightChild = current;
                current = current->leftChild;
            }
            else
            {
                pre->rightChild = nil;
                count++;
                current = current->rightChild;
            }
        }
    }
    return count;
}

int MovieTree::countLongestPath(MovieNode *node) //recursive function for finding longest path
{
    if(node == nil)
        return 0;
    else
    {
        int lPath = countLongestPath(node->leftChild);
        int rPath = countLongestPath(node->rightChild);
        if(lPath >rPath)
            return (lPath + 1);
        else
            return (rPath + 1);
    }
}

MovieNode *MovieTree::searchMovieTree(MovieNode *node, string title)
{
    MovieNode *temp = node;
    while(temp != nil) //traverses through the tree until movie is found or the bottom of the tree is reached
    {
        if(temp->title == title)
            break;
        if(temp->title < title)
            temp = temp->rightChild;
        else if (temp->title > title)
            temp = temp->leftChild;
    }
    return temp;
}

MovieTree::~MovieTree()
{
    DeleteAll(root); //delete all the nodes of the tree when exiting the program
}
