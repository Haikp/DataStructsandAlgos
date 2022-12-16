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

    numProduct.resize(maxDigitSize);
    
    for (int i = 0; i < num2.size(); i++){
        for (int j = 0; j < i; j++){
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
    totalSum.resize(maxDigitSize);

    //for (int i = numProduct[i].size())

    cout << "num1: " << numProduct[0].size() << endl;
    cout << "num2: " << numProduct[1].size() << endl;
    cout << "num3: " << numProduct[2].size() << endl;

    /*

    int sum = 0;
    int remainder = 0;
    int excessNum = 0;

    for (int j = 0; j < maxDigitSize; j++){
        for (int i = 0; i < num2.size(); i++){
            if (numProduct[i][j] < 0 || numProduct[i][j] > 10){
                continue;
            }
            sum += numProduct[i][j];
        }

        sum += excessNum;
        remainder = (sum % 10);
        excessNum = (sum / 10);
        totalSum.push_back(remainder);
    }

    if (excessNum != 0){
        if (excessNum > 10){
            totalSum.push_back(excessNum%10);
        }

        totalSum.push_back(excessNum/10);
    }

    cout << "Sum: ";

    for (int i = totalSum.size() - 1; i >= 0; i--){
        cout << totalSum[i];
    }
    
    cout << endl;
    */

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
        t_lock.lock();
        cout << num1[i] << "*" << num2 << "+" << excessNum << " = " << multProduct << endl;
        t_lock.unlock();
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

/*
check what numbers are in the 2D vector
* do the math by hand some where
* attempt to cout the numbers to see what is inside the 2D vector
* fix adding algorithm

*/