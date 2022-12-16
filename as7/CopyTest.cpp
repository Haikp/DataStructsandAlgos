#include "hashMap.hpp"
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    hashMap<char, int> hash1;
    hashMap<char, int> hash2;

    for (int i = 0; i < 3; i++)
        hash1['A' + i] = i + 10;

    hash2 = hash1;

    hash2['C'] = 67;
    hash2['A'] = 99;

    hashMap<char, int> hash3(hash2);

    hash3['B'] = 115;
    hash3['A'] = 116;

    for (int i = 0; i < 3; i++)
        cout << hash1[i + 'A'] << " " << hash2[i + 'A'] << " " << hash3[i + 'A'] << endl;

    return 0;
}