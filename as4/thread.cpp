#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
using namespace std;

void getNumInputs(vector<short>&);
void multiply(vector<short>, int, int);

vector<vector<short>> numProduct;

mutex t_lock;

int main(){
    vector<short> num1;
    vector<short> num2;

    cout << "Enter number1: ";
    getNumInputs(num1);
    cout << "Enter number2: ";
    getNumInputs(num2);

    int maxThreads = thread::hardware_concurrency();
    int maxDigitSize = num1.size() + num2.size();
    vector<thread> threadPool;

    numProduct.resize(num2.size());

    for (int i = num2.size() - 1; i >= 0; i--){
        for (int j = numProduct.size() - 1; j > i; j--){
            numProduct[i].push_back(0);
        }

        threadPool.push_back( thread( multiply, num1, num2[i], i));
        if (threadPool.size() % maxThreads == 0){
            for (int j = 0; j < threadPool.size(); j++){
                threadPool[j].join();
            }

            threadPool.clear();
        }
    }

    for (int i = 0; i < threadPool.size(); i++){
        threadPool[i].join();
    }

    threadPool.clear();

    vector<int> totalSum;
/*
    cout << "numProduct.size(): " << numProduct.size() << endl;
    cout << "numProduct[0].size(): " << numProduct[0].size() << endl;
    cout << "numProduct[1].size(): " << numProduct[1].size() << endl;
    cout << "numProduct[2].size(): " << numProduct[2].size() << endl;
*/
    cout << "2D vector contents: " << endl;

    for (int i = 0; i < numProduct.size(); i++){
        for (int j = 0; j < numProduct[i].size(); j++){
            cout << numProduct[i][j] << " ";
        }

        cout << endl;
    }

    int sum = 0;
    int remainder = 0;
    int excessNum = 0;

    for (int j = 0; j < numProduct[0].size(); j++){
        for (int i = 0; i < numProduct.size(); i++){
            //add if i is less than numProduct[i].size()
            if (j < numProduct[i].size()){
                sum += numProduct[i][j];
            }
        }
        
        sum += excessNum;
        remainder = (sum % 10);
        excessNum = (sum / 10);

        totalSum.push_back(remainder);
        sum = 0;
    }

    if (excessNum != 0){
        while (excessNum > 10){
            int tempNum = excessNum % 10;
            excessNum = excessNum / 10;
            totalSum.push_back(tempNum);
        }

        totalSum.push_back(excessNum);
    }
//add if it meets the condition, if i is less than numProduct[i].size()
    cout << "Sum: ";
    cout << totalSum.size() << endl;

    for (int i = totalSum.size() - 1; i >= 0; i--){
        cout << totalSum[i];
    }
    
    cout << endl;

    return 0;
}

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

void multiply(vector<short> num1, int num2, int iter){
    int multProduct = 0;
    int remainder = 0;
    int excessNum = 0;

    for (int i = num1.size() - 1; i >= 0; i--){
        multProduct = num1[i] * num2 + excessNum;
        //t_lock.lock();
        //cout << num1[i] << "*" << num2 << "+" << excessNum << " = " << multProduct << endl;
        //t_lock.unlock();
        //take the ones value place
        remainder = (multProduct % 10);
        //take the tens value place
        excessNum = (multProduct / 10);
        numProduct[iter].push_back(remainder);
    }

    if (excessNum != 0){
        numProduct[iter].push_back(excessNum);
    }
}


/*while the thread runs through the multiply function, add the 0's to the 2D vector according to i, if i = 1, then add a single 0 to the end of the vector
on the same row number as well.

i = row
j = column

multiply function will add into the 2D vector while the threads are running

add function will go in to a cell of the 2D array, if it is NULL do not add


OR------------------------

push back the amount of 0's in the 2D vector as stated above, however start on the left side
you will be inputing the numbers backwards, and when you add the columns together, put it back in the correct orientation
*/