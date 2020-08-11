#include "MovieTree.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

MovieTree::MovieTree()
{
    //ctor
}

void MovieTree::printMovieInventory() //uses in order traversal to print movies
{
    MovieNode *current = new MovieNode;
    MovieNode *pre = new MovieNode;
    if(root == NULL)
        cout << "Empty" << endl;
    current = root;
    while (current != NULL)
    {
        if(current->leftChild == NULL)
        {
            cout << "Movie: " << current->title << " " << current->quantity << endl;
            current = current->rightChild;
        }
        else
        {
            pre = current->leftChild;
            while(pre->rightChild != NULL && pre->rightChild != current)
            {
                pre = pre->rightChild;
            }
            if(pre->rightChild == NULL)
            {
                pre->rightChild = current;
                current = current->leftChild;
            }
            else
            {
                pre->rightChild = NULL;
                cout << "Movie: " << current->title << " " << current->quantity << endl;
                current = current->rightChild;
            }
        }
    }
}

int MovieTree::countMovieNodes() //in order traversal with a counter
{
    MovieNode *current = new MovieNode;
    MovieNode *pre = new MovieNode;
    int count = 0;
    if(root == NULL)
        cout << "Empty" << endl;
    current = root;
    while (current != NULL)
    {
        if(current->leftChild == NULL)
        {
            count++;
            current = current->rightChild;
        }
        else
        {
            pre = current->leftChild;
            while(pre->rightChild != NULL && pre->rightChild != current)
            {
                pre = pre->rightChild;
            }
            if(pre->rightChild == NULL)
            {
                pre->rightChild = current;
                current = current->leftChild;
            }
            else
            {
                pre->rightChild = NULL;
                count++;
                current = current->rightChild;
            }
        }
    }
    return count;
}

void MovieTree::deleteMovieNode(std::string title)
{
    MovieNode *n = root;
    while(n != NULL) //finds the movie to delete
    {
        if(title < n->title)
            n = n->leftChild;
        else if(title > n->title)
            n = n->rightChild;
        else
            break;
    }
    if(n == NULL)
    {
        cout << "Movie not found." << endl;
    }
    else
    {
        if(n->rightChild != NULL) //replaces it with right child
        {
            MovieNode *right = n->rightChild;
            if(n->leftChild != NULL)
                right->leftChild = n->leftChild;
            if(n->parent->rightChild == n)
                n->parent->rightChild = right;
            else
                n->parent->leftChild = right;
            right->parent = n->parent;
            delete n;
        }
        else if(n->leftChild != NULL) //if no right child, replaces with leftchild
        {
            MovieNode *left = n->leftChild;
            if(n->parent->rightChild == n)
                n->parent->rightChild = left;
            else
                n->parent->leftChild = left;
            left->parent = n->parent;
            delete n;
        }
        else //if no children, just delete the movie
        {
            if(n->parent->rightChild == n)
                n->parent->rightChild = NULL;
            else
                n->parent->leftChild = NULL;
            delete n;
        }
    }
}


void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    MovieNode *newNode = new MovieNode(ranking, title, releaseYear, quantity);
    MovieNode *tmp = root;
    MovieNode *parent = NULL;
    while(tmp != NULL) //adds to the tree into alphabetical order
    {
        parent = tmp;
        if(newNode->title < tmp->title)
            tmp = tmp->leftChild;
        else
            tmp = tmp->rightChild;
    }
    if(parent == NULL)
        root = newNode;
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
}

void MovieTree::findMovie(std::string title)
{
    MovieNode *movie = search(title); //uses search to find the movie then print info
    if(movie != NULL)
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

void MovieTree::rentMovie(std::string title)
{
    MovieNode *movie = search(title); //find the movie
    if(movie != NULL)
    {
        movie->quantity = movie->quantity - 1; //reduce quantity in stock
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

void MovieTree::DeleteAll(MovieNode * node) //use this for the post-order traversal deletion of the tree
{
    if(node != NULL)
    {
        if(node->leftChild != NULL)
            DeleteAll(node->leftChild);
        if(node->rightChild != NULL)
            DeleteAll(node->rightChild);
        cout << "Deleting: " << node->title << endl;
        delete node;
    }
}

void MovieTree::printMovieInventory(MovieNode * node)
{
    cout << node->quantity << endl;
}

void MovieTree::countMovieNodes(MovieNode *node, int *c)
{
 //not needed
}

MovieNode* MovieTree::search(std::string title) //find the movie
{
    MovieNode *temp = root;
    while(temp != NULL)
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

MovieNode* MovieTree::searchRecursive(MovieNode *node, std::string value)
{
    MovieNode *searchNode = root;
    if(searchNode == NULL)
    {
        return searchNode;
    }
    else
    {
        if(searchNode->title == value)
            return searchNode;
        else if(searchNode->title > value)
            return searchRecursive(searchNode->leftChild, value);
        else if(searchNode->title < value)
            return searchRecursive(searchNode->rightChild, value);
        else
            return NULL;
    }
}

MovieNode* MovieTree::treeMinimum(MovieNode *node) //never needed
{
    while(node->leftChild != NULL)
        node = node->leftChild;
    return node;
}

MovieTree::~MovieTree()
{
    DeleteAll(root);
}
