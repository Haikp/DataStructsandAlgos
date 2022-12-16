#include <iostream>
#include <fstream>
#include "jl.h"

using namespace std;

int main(int args, char * argv[]){
    LL<int> ll;
    LL<int>::iterator it;
    LL<int>::iterator end(nullptr);
    ifstream iFile;
    iFile.open(argv[1]);

    int data;

    while(!iFile.eof()){
        iFile >> data;
        if(iFile.eof()){
            break;
        }
        ll.tailInsert(data);
    }
    

    LL<int>::iterator i,j,nil,next(nullptr);
    LL<int>::iterator maxPos;
    LL<int>::iterator atJ;

    int max = 0;

    j = nil;
    
    for(i = ll.begin(); i != j; j--){
        //maxpos is at i
        //max number is i
        maxPos = i;
        max = *i;

        //moves beginning iterator over 
        i++;    

        //while loop to find max element
        while(i != j){
            //checks if max is greater than i's data
            if(max < *i){   

                //dereferences i and sets that as max num
                //saves that position in maxPos iterator 
                max = *i;
                maxPos = i;

            }

            //traverses through ll 
            i++;
        }

        //checks to see if j is nil
        //sets that to the tail
        //goes through once to find the end of the ll 
        if(j == nil){
            j = ll.end();
        }

            
        if(*maxPos > *j){
            ll.swapNodes(maxPos,j);
            j = maxPos;
        }

        i = ll.begin();
    }   
    

    for (it = ll.begin(); it != NULL; it++){
        cout << *it << endl;
    }
    
}   