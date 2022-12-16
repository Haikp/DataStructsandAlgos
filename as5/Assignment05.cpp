/******************************************
 * My Name is   : Kelvin Do
 * My NSHEID is : 2001770482
 * My Email is  : dok7@unlv.nevada.edu
 * Assignment05.cpp Does the Following: 
 * constructs a binary tree of rooms
 * places cameras within rooms efficiently
 * a camera can see the room its in, and adjadcent rooms as well
 * determine how many cameras are needed depending on the binary tree layout
******************************************/
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "binTree.hpp"
using namespace std;

struct visibilityType
{
    int id;
    bool camera;
    bool seen;

    bool operator==(int x)
    {
        return id == x;
    }
};

vector<visibilityType> parseLine(string);
void cameraPlacement(binTree<visibilityType>::binTreeIterator, int &);

int main(int argc, char *argv[])
{
    //take in a file of values for the binary tree
    ifstream inFile;
    inFile.open(argv[1]);

    string cases;
    int totalCases;
    //the first line within the file is the amount of trees
    getline(inFile, cases);
    totalCases = stoi(cases);

    //loop through the amount of trees that need to be created
    for (int i = 0; i < totalCases; i++)
    {
        vector<visibilityType> caseValues;
        binTree<visibilityType> constructTree;
        int cameraQuantity = 0;
        //take the first tree layout
        getline(inFile, cases);
        //parse the line of data in to a vector
        caseValues = parseLine(cases);
        //construct the tree with the given vector
        constructTree.buildTree(caseValues);
        //create an iterator that will traverse the tree
        binTree<visibilityType>::binTreeIterator iter(constructTree.rootIterator());
        //cout the desired information
        cout << "Case " << i + 1 << ":  ";
        //if the tree a singular room by itself, it requires only 1 camera, edge case
        if (iter.leftChild() == NULL && iter.rightChild() == NULL)
        {
            cameraQuantity = 1;
        }

        //begin to determine the amount of cameras required
        cameraPlacement(iter, cameraQuantity);
        cout << cameraQuantity << " cameras needed" << endl;
        constructTree.~binTree();
    }

    return 0;
}

/**********************************************
 *  parseLine
 *      parameter: take in a line of numbers separated by spaces
 *      insert the values in to a vector
 *      return the vector of parsed data
**********************************************/
vector<visibilityType> parseLine(string line)
{
    stringstream s(line);
    vector<visibilityType> parsedLine;
    visibilityType n;

    while (s >> n.id)
    {
        n.seen = n.camera = false;
        parsedLine.push_back(n);
    }

    return parsedLine;
}

/**********************************************
 *  camera placement
 *      parameter: take in the iterator attached to a tree
 *      parameter: pass by reference the amount of cameras needed
 *      traverse postorder through binary tree
 *      begin to place cameras as defined by the if statements
**********************************************/
void cameraPlacement(binTree<visibilityType>::binTreeIterator iter, int &camQuantity)
{
    //if there is no room that the iter is pointing to, return
    if (iter == NULL)
    {
        return;
    }

    //postorder traversal
    cameraPlacement(iter.leftChild(), camQuantity);
    cameraPlacement(iter.rightChild(), camQuantity);

    //if the iter is pointing to a leaf, return
    if (iter.leftChild() == NULL && iter.rightChild() == NULL)
    {
        return;
    }

    bool needsCamera = true;
    //check if there is a left node
    if (iter.leftChild() != NULL)
    {
        //check if the left node has a camera
        if ((*iter.leftChild()).camera == true)
        {
            //if it does, set the current room as seen
            (*iter).seen = true;
            //the current room does not need a camera
            needsCamera = false;
            //however if a right node exists as well
            if (iter.rightChild() != NULL)
            {
                //if the right node is unseen
                if ((*iter.rightChild()).seen == false)
                {
                    //a camera is needed
                    needsCamera = true;
                }
                else
                {
                    return;
                }
            }
        }
    }

    //check if there is a right node
    if (iter.rightChild() != NULL)
    {
        //check if the right node has a camera
        if ((*iter.rightChild()).camera == true)
        {
            //the room is already seen
            (*iter).seen = true;
            //the room does not need a camera
            needsCamera = false;
            //however if there exists a left child
            if (iter.leftChild() != NULL)
            {
                //if the left node is unseen
                if ((*iter.leftChild()).seen == false)
                {
                    //then a camera is needed in the current room
                    needsCamera = true;
                }
                else
                {
                    return;
                }
            }
        }
    }

    //if the current room needs a camera
    if (needsCamera)
    {
        //place a camera
        (*iter).camera = true;
        camQuantity++;
        //mark the appropriate rooms as seen if they exist
        (*iter).seen = true;
        //if left node exists, mark as seen
        if (iter.leftChild() != NULL)
        {
            (*iter.leftChild()).seen = true;
        }

        //if right node exists, mark as seen
        if (iter.rightChild() != NULL)
        {
            (*iter.rightChild()).seen = true;
        }
    }

    return;
}
