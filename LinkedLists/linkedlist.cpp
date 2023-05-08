/******************************************
 * implementation file
 * has int main()
 * opens a file of random numbers
 * inserts each number into a unique node of a linekd list
 * use a selection sort to organize in size
 * cout the linked list from least to greatest
******************************************/
#include <iostream>
#include <fstream>
#include "LL.h"
using namespace std;

int main(int argc, char * argv[]){
    LL<int> lst;
    LL<int>::iterator it;
    LL<int>::iterator end(NULL);

    //take in the file
    ifstream inFile;
    inFile.open(argv[1]);

    int num = 0;

    //put values in to the linked list
    while (!inFile.eof()){

        inFile >> num;

        if (inFile.eof()){
            break;
        }

        lst.tailInsert(num);
    }

    //establish pointers to traverse linked list
    LL<int>::iterator i, j, nil(NULL);
    LL<int>::iterator maxPos;
    int max;

    j = nil;

    //selection sort
    for (i = lst.begin(); i != j; j--){
        //point to the last node sorted
        maxPos = i;
        max = *i;
        i++;
        
        //checks the value of the node that j itself is pointing to
        //searches for largest value
        if (j != nil){
            j++;

            while (i != j){
                if (max < *i){
                    maxPos = i;
                    max = *i;
                }

                i++;
            }

            j--;
        }
        
        //searches for largest value
        else{
            while (i != j){
                if (max < *i){
                    maxPos = i;
                    max = *i;
                }

                i++;
            }
        }

        //first case scenario, j may contain the largest value
        //use iterator j once the list has been sifted through once
        if (j == nil){
            j = lst.end();
        }

        //swap the largest value with the last element
        lst.swapNodes(maxPos, j);
        //reset iterators for next loop
        i = lst.begin();
        j = maxPos;

    }

    //cout the linked list
    for (it = lst.begin(); it != NULL; it++){
        cout << *it << endl;
    }
}
