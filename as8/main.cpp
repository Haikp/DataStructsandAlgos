/******************************************
 * My Name is   : Kelvin Do
 * My NSHEID is : 2001770482
 * My Email is  : dok7@unlv.nevada.edu
 * Assignment08.cpp Does the Following: 
 * Open up a file of numbers
 * insert the numbers into an array while bubblingUp the values based on how large the number is
 * everytime a new number is inserted, delete the largest number
 * cout the k-th largest number each time
******************************************/
#include <iostream>
#include <fstream>
#include "priorityQ.hpp"
using namespace std;

int main()
{
    //obtain file
    ifstream inFile;
    string fileName;
    cout << "Enter filename: ";
    cin >> fileName;
    inFile.open(fileName);
    
    //the k-th element to be obtaining
    int k = 0;
    inFile >> k;

    int num = 0;
    //establish array we will be using
    priorityQ<int> numArray(k + 1);
    //for loop to obtain the first 12 elements
    for (int i = 0; i < k; i++)
    {
        inFile >> num;
        numArray.insert(num);
    }

    //declare the first 12-th largest number
    cout << "Initial " << k << "-th largest number: " << numArray.getHighestPriority() << endl;

    //keep track of the previous largest number
    int prevLargest = numArray.getHighestPriority();
    while (!inFile.eof())
    {
        inFile >> num;
        if (inFile.eof())
        {
            break;
        }

        //insert a new number in to the heap
        numArray.insert(num);
        //delete the current head
        numArray.deleteHighestPriority();
        //if there is a new largest number, cout it
        if (numArray.getHighestPriority() != prevLargest)
        {
            cout << "New " << k << "-th largest number: " << numArray.getHighestPriority() << endl;
        }

        //adjust the known previous largest number accordingly
        prevLargest = numArray.getHighestPriority();
    }
    
    cout << "Final " << k << "-th largest number: " << numArray.getHighestPriority() << endl;
}
