#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "hashMap.hpp"
using namespace std;

int main()
{
    fstream inFile;
    string fileName;
    cout << "Filename: ";
    cin >> fileName;
    inFile.open(fileName);

    vector<string> words;
    string word;
    while(!inFile.eof())
    {
        inFile >> word;
        if (inFile.eof()){
            break;
        }

        words.push_back(word);
    }

    vector<vector<string>> anagrams;
    vector<hashMap<char, bool>> lettersUsed;
    anagrams.resize(words.size());

    for (int i = 0; i < words.size(); i++)
    {
        anagrams[i].push_back(words[i]);
    }

/*
    for (int i = 0; i < anagrams.size(); i++)
    {
        cout << anagrams[i][0] << endl;
    }
*/

    lettersUsed.resize(anagrams.size());

    for (int i = 0; i < anagrams.size(); i++)
    {
        for (int j = 0; j < word.size(); j++)
        {
            string currWord = anagrams[i][0];
            char letter = currWord[j];
            lettersUsed[i][letter] = true;
        }
    }

    //int uniqueAnagrams = 0;
    bool viableAnagram[anagrams.size()];
    //loop through all words of anagrams
    for (int i = 0; i < anagrams.size(); i++)
    {
        if (anagrams[i][0].size() == 0)
        {
            continue;
        }

        //uniqueAnagrams++;
        //set entire array of possibleAnagrams to true
        for (int j = 0; j < anagrams.size(); j++)
        {
            viableAnagram[j] = true;
        }

        //loop thorugh each letter of a word
        for (int j = 0; j < word.size(); j++)
        {
            string currWord = anagrams[i][0];
            char letter = currWord[j];

            //check if the letter exists in other words
            for (int k = 0; k < anagrams.size(); k++)
            {
                //only search through the words marked as potential anagrams
                if (viableAnagram[k] == true)
                {
                    if (lettersUsed[k][letter] == false)
                    {
                        viableAnagram[k] = false;
                    }
                }
            }
        }

        //int anagramCounter = 1;
        for (int j = i + 1; j < anagrams.size(); j++)
        {
            if (viableAnagram[j])
            {
                //anagramCounter++;
                anagrams[i].push_back(words[j]);
                anagrams[j][0].clear();
            }
        }

        //cout << "Group " << uniqueAnagrams << " contains " << anagramCounter << " words" << endl;
    }

    int uniqueAnagrams = 0;
    for (int i = 0; i < anagrams.size(); i++)
    {
        if (anagrams[i][0].size() == 0)
        {
            continue;
        }

        uniqueAnagrams++;
        for (int j = 0; j < anagrams[i].size(); j++)
        {
            cout << "i = " << i << " j = " << j << endl;
            cout << anagrams[i][j] << endl;
        }
    }
}