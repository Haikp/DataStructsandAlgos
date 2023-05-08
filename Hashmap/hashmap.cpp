/******************************************
 * Open up a file of words
 * begin hashing the letters of the words
 * determine what letter exists in each word
 * check to see which words are anagrams of one another
 * sort the anagrams in to their own groups
 * cout the amount of anagram groups and the quantity of them in greatest to least
******************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "hashMap.hpp"
using namespace std;

int main()
{
    fstream inFile;
    string fileName;
    cout << "Filename: ";
    //obtain and open the file
    cin >> fileName;
    inFile.open(fileName);

    vector<string> words;
    string word;

    //insert the contents of the file in to a vector of strings
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

    //place the words into a 2d vector for sorting purposes later on
    for (int i = 0; i < words.size(); i++)
    {
        anagrams[i].push_back(words[i]);
    }

    lettersUsed.resize(anagrams.size());

    //begin hashing each letter of each word respectively
    //loop takes a word
    for (int i = 0; i < anagrams.size(); i++)
    {
        //loop takes a letter from the word
        for (int j = 0; j < word.size(); j++)
        {
            string currWord = anagrams[i][0];
            char letter = currWord[j];
            //hash the letter by setting it to true, making it exist in the current word
            lettersUsed[i][letter] = true;
        }
    }

    int uniqueAnagrams = 0;
    bool viableAnagram[anagrams.size()];
    //loop through all words of anagrams
    for (int i = 0; i < anagrams.size(); i++)
    {
        //if there is no word in the anagram, continue to the next word
        if (anagrams[i][0].size() == 0)
        {
            continue;
        }

        //increment the amount of unique anagrams
        uniqueAnagrams++;
        //set entire array of possibleAnagrams to true
        for (int j = 0; j < anagrams.size(); j++)
        {
            //keep track of which word are anagrams of each other
            viableAnagram[j] = true;
        }

        //loop through each letter of a word
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
                    //if the word does not exist in the potential anagrams, set to false
                    if (lettersUsed[k][letter] == false)
                    {
                        viableAnagram[k] = false;
                    }
                }
            }
        }

        //loop through the list of anagrams
        for (int j = i + 1; j < anagrams.size(); j++)
        {
            //if the words are a anagram of each other,
            if (viableAnagram[j])
            {
                //move the anagrams into its own row within the 2d vector
                anagrams[i].push_back(words[j]);
                //delete the word's previous location
                anagrams[j][0].clear();
            }
        }
    }

    vector<int> anagramGroups;
    anagramGroups.resize(uniqueAnagrams);

    //cout amount of anagram groups
    cout << "Amount of groups: " << uniqueAnagrams << endl;
    //loop through and put all the sizes into a for loop
    for (int i = 0; i < anagrams.size(); i++)
    {
        //if the slot is not empty from moving the words around previously,
        if (anagrams[i][0].size() != 0)
        {
            //push the size back in to the vector of anagram sizes
            anagramGroups.push_back(anagrams[i].size());
        }
    }

    //sort the list of anagram sizes by greatest to least
    sort(anagramGroups.begin(), anagramGroups.end(), greater<int>());

    //cout the group number and amount of anagrams in the group
    for (int i = 0; i < uniqueAnagrams; i++)
    {
        cout << "Group " << i + 1 << " contains " << anagramGroups[i] << " words" << endl;
    }
}