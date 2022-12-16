/******************************************
 * My Name is   : Jadon Loi
 * My NSHEID is : 5006634927
 * My Email is  : loij1@unlv.nevada.edu
 * This Program Does the Following: 
 * It reads in words from a file and inserts it into a vector of strings
 * It then creates a vector of anagrams each with 1 word and a vector of hashMaps
 * with letters from each word
 * Uses the hashmap to find if the current word and iterating word are anagrams
 * Inserts that word into the current words vector and outputs the groups of anagrams
 * and how many they have
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
    ifstream iFile;
    string file;

    //outputs message to open and reads in file
    cout << "Filename: ";
    cin >> file;
    iFile.open(file);

    vector<string> words;
    string word;

    //pushes word into vector
    while (true)
    {
        if (iFile.eof())
        {
            break;
        }
        iFile >> word;
        words.push_back(word);
    }

    //creates 2d vector of anagrams
    //pushes each word in words vector to anagrams
    vector<vector<string>> anagrams;
    for (int i = 0; i < words.size() - 1; i++)
    {
        vector<string> temp;
        temp.push_back(words[i]);
        anagrams.push_back(temp);
    }

    //2d vector of hashMaps
    //resizes and allocates the vector size to anagrams size
    vector<hashMap<char, bool>> lettersUsed;
    lettersUsed.resize(anagrams.size());

    //loop to insert each letter from each word to the hashMap
    //gives it a key and value
    for (int i = 0; i < anagrams.size(); i++)
    {
        string word;
        word = anagrams[i][0];
        for (int j = 0; j < word.size(); j++)
        {
            char index = word[j];
            lettersUsed[i][index] = true;
        }
    }

    //counter to see how many correct letters are in the checking word
    int letterCounter = 0;

    //loop to go through the anagram
    for (int i = 0; i < anagrams.size(); i++)
    {

        //start word
        string word;

        //if the current anagram has no elements, move on
        if (anagrams[i].size() == 0)
        {
            continue;
        }

        //outer loop word
        word = anagrams[i][0];

        //inner loop to find words that can be anagrams
        for (int j = 0; j < anagrams.size(); j++)
        {
            //checking word
            string check;

            //if current anagram has no elements, move on
            if (anagrams[j].size() == 0)
            {
                continue;
            }

            //inner loop word
            check = anagrams[j][0];

            //goes through each character in outer loop word
            for (int charIndex = 0; charIndex < word.size(); charIndex++)
            {
                //character in first string
                char character = word[charIndex];

                //checks if there is a the current character is present in the inner words hashtable
                //if letters are not found in hashmap changes checking word's letter to false
                if (lettersUsed[i][character] == lettersUsed[j][character])
                {
                    //increases count to check
                    letterCounter++;
                }
                else
                {
                    //sets the character in the second hashtable to false
                    lettersUsed[j][character] = false;
                }
            }

            //if all letters match the current word in hMap
            if (letterCounter == word.size())
            {
                //no duplicates
                if (check != word)
                {
                    //inserts to outer loop anagram's vector and clears inner loops vector
                    anagrams[i].insert(anagrams[i].end(), check);
                    anagrams[j].clear();
                }
            }

            //sets the counter to 0 for next iteration
            letterCounter = 0;

            //change everything back to true in hmap for next usage
            for (int i = 0; i < check.size(); i++)
            {
                char ind = check[i];
                lettersUsed[j][ind] = true;
            }
        }
    }
    
    vector<int> sizes;
    //stores all sizes to a vector and sorts it
    for(int i = 0; i < anagrams.size(); i++){
        if(anagrams[i].size() != 0)
            sizes.push_back(anagrams[i].size());
    }
    sort(sizes.begin(), sizes.end(), greater<int>());

    //outputs the amount of groups and how many elements are in each group 
    cout << "Amount of groups: " << sizes.size() << endl;
    for(int i = 0; i < sizes.size(); i++)
        if(sizes[i] != 0){
            cout << "Group " << i+1 << " contains " <<  sizes[i] << " words" << endl;
        }
    


    for(int i = 0; i < anagrams.size(); i++){
        cout << "anagrams " << i;
        for(int j = 0; j < anagrams[i].size(); j++){
            if(anagrams[i].size() != 0)
                cout << " " << anagrams[i][j] << " ";
            else
                continue;
        }
        cout << endl;
    }
    iFile.close();
    
    return 0;
}