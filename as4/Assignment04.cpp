/******************************************
 * My Name is   : Kelvin Do
 * My NSHEID is : 2001770482
 * My Email is  : dok7@unlv.nevada.edu
 * Assignment04.cpp Does the Following: 
 * take in two inputs, insert integers of any size
 * compute long multiplication
 * cout the answer
 * compute using threads by multi parallelize method
******************************************/
#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
using namespace std;

void getNumInputs(vector<short>&);
void multiply(vector<short>, int, int);

vector<vector<short>> numProduct;

int main(){
    vector<short> num1;
    vector<short> num2;

    //take in the two integers
    cout << "Enter number1: ";
    getNumInputs(num1);
    cout << "Enter number2: ";
    getNumInputs(num2);

    //establish amount of possible threads with in current pc
    int maxThreads = thread::hardware_concurrency();
    int maxDigitSize = num1.size() + num2.size();
    vector<thread> threadPool;

    //resize the 2D vector to the size of the second number
    //when doing multiplication, it will require a certain amount of rows, 
    //of which is the same amount as the length of the second integer
    numProduct.resize(num2.size());

    //iterate through the rows of the column
    for (int i = num2.size() - 1; i >= 0; i--){
        //depending on the row iteration,
        for (int j = numProduct.size() - 1; j > i; j--){
            //pushback a certain amount of zero's
            numProduct[i].push_back(0);
        }

        //spawn in threads and begin to compute multiplication
        threadPool.push_back( thread( multiply, num1, num2[i], i));
        //manage the amount of threads to fit to current pc's standards
        if (threadPool.size() % maxThreads == 0){
            for (int j = 0; j < threadPool.size(); j++){
                threadPool[j].join();
            }

            //clear for next set of threads
            threadPool.clear();
        }
    }

    //clear excess amount of threads after final computations
    for (int i = 0; i < threadPool.size(); i++){
        threadPool[i].join();
    }

    threadPool.clear();

    vector<int> totalSum;

    int sum = 0;
    int remainder = 0;
    int excessNum = 0;

    //begin adding the computations
    //iterate through the longest integer after the multiplcation process
    for (int j = 0; j < numProduct[0].size(); j++){
        //iterate through the columns of the 2D vector
        for (int i = 0; i < numProduct.size(); i++){
            //the size of the product in the vector is with in range of the iterator
            if (j < numProduct[i].size()){
                //add the integers in the column of the 2D vector
                sum += numProduct[i][j];
            }
        }
        
        //add the integers "carried over" from the previous computation
        sum += excessNum;
        //find the ones value
        remainder = (sum % 10);
        //find the value that will be "carried over" to the next computation
        excessNum = (sum / 10);

        //the ones value is then pushed back into the vector
        totalSum.push_back(remainder);
        //reset the sum for next column of addition
        sum = 0;
    }

    //if the amount carried over is more than 0,
    if (excessNum != 0){
        //while the value is greater than 10
        while (excessNum >= 10){
            //take the ones place of the excessNum
            int tempNum = excessNum % 10;
            //take tje rest of the remainder
            excessNum = excessNum / 10;
            //pushback the ones place into the totalSum
            totalSum.push_back(tempNum);
        }

        //pushback the value into the totalSum
        totalSum.push_back(excessNum);
    }

    bool ansIs0 = true;
    //cout the product of the two integers
    cout << "The product is: ";
    //check if the solution is 0
    for (int i = totalSum.size() - 1; i >= 0; i--){
        int ans = totalSum[i];
        if (ans != 0){
            ansIs0 = false;
            break;
        }
    }

    //if the solution is only 0, then cout 0 once
    if (ansIs0){
        cout << "0";
    }
    //else cout the whole answer
    else{
        for (int i = totalSum.size() - 1; i >= 0; i--){
            cout << totalSum[i];
        }
    }

    cout << endl;
    
    return 0;
}

/**********************************************
 *  getNumInputs
 *      take in the given input at as string
 *      take the string one char at a time
 *      input the char in to its own element within the vector
**********************************************/ 
void getNumInputs(vector<short>& numberVector){
    //take in a number as a string
    string num;
    cin >> num;
    //separate the "number" in to its individual and push it in to a vector
    for (int i = 0; i < num.size(); i++){
        //change from char to int
        numberVector.push_back(num[i] - '0');
    }
}

/**********************************************
 *  multiply
 *      parameters: the first in input, one of the elements of the second int input, iter
 *      multiply the element of the second int to all of the first int
 *      pushback the products into the 2D vector
 *      as to where it pushes back, each thread will have its designated location, or 'iter'
 *      to avoid conflicting pushbacks, each thread will work with one of the rows on the 2D vector
**********************************************/ 
void multiply(vector<short> num1, int num2, int iter){
    int multProduct = 0;
    int remainder = 0;
    int excessNum = 0;

    //iterate through the first integer input
    for (int i = num1.size() - 1; i >= 0; i--){
        //multiply an integer from the second int input with every integer in the first input, 
        //add the "carry over" from previous computations
        multProduct = num1[i] * num2 + excessNum;
        //take the ones place value of the product
        remainder = (multProduct % 10);
        //compute the "carry over" value
        excessNum = (multProduct / 10);
        //push in the ones place value into the 2D vector,
        //each thread has its own designated 'iter' location in the 2D vector
        //each thread will be pushing back values in to its own row of numbers
        numProduct[iter].push_back(remainder);
    }

    //if there is still "carry over" values
    if (excessNum != 0){
        //pushback the "carry over"
        numProduct[iter].push_back(excessNum);
    }
}
