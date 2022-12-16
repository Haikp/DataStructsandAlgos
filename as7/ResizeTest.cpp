#include "hashMap.hpp"
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    hashMap<char, int> testMap;
    vector<char> letters;

    for (int i = 0; i < 90; i++)
        letters.push_back('!' + i);

    for (int i = 0; i < letters.size(); i++)
        testMap[letters[i]] = i;
    

    for (int i = 0; i < letters.size(); i++)
        cout << testMap[letters[i]] << endl;

    return 0;
}